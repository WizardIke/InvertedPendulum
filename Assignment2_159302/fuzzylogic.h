#ifndef __FUZZYLOGIC_H__
#define __FUZZYLOGIC_H__

#include <math.h>
#include <set>
#include <stack>
#include <ctime>
#include <cstddef>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <deque>
#include <set>
#include <random>
#include <cassert>

#undef min
#undef max

//Input parameters
enum { in_theta, in_theta_dot, in_x, in_x_dot };
enum { in_theta_combined, in_x_combined, number_of_combined_inputs};

//Fuzzy sets
enum { in_nl, in_ns, in_ze, in_ps, in_pl, number_of_input_regions};

//Fuzzy output terms
enum { out_nvvl, out_nvl, out_nl, out_nm, out_ns, out_nvs, out_ze, out_pvs, out_ps, out_pm, out_pl, out_pvl, out_pvvl, number_of_outputs };

float min_of(float values[], unsigned int number_of_inputs);

class TrapezoidFunction 
{
	float a, b, c, d, l_slope, r_slope;
public:
	TrapezoidFunction() {}
	TrapezoidFunction(float x1, float x2, float x3, float x4);
	float operator()(float x) const;

	friend std::ostream& operator<<(std::ostream& out, const TrapezoidFunction& trap)
	{
		out << trap.a << ' ' << trap.b << ' ' << trap.c << ' ' << trap.d;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, TrapezoidFunction& trap)
	{
		float a, b, c, d;
		in >> a >> b >> c >> d;
		trap = TrapezoidFunction(a, b, c, d);
		return in;
	}
};

template<std::size_t numberOfInputs>
struct Rule
{
	unsigned char input_fuzzy_set[numberOfInputs];
	unsigned char out_fuzzy_set;
};

template<unsigned char numberOfInputs, std::size_t numberOfRules, unsigned char numberOfFuzzySets, size_t numberOfOutputs>
struct Famm
{
	constexpr static float too_small_total_weight = 1e-6f;

	Rule<numberOfInputs> rules[numberOfRules];
	TrapezoidFunction input_membership_functions[numberOfFuzzySets][numberOfInputs];
	float output_values[numberOfOutputs];

	float calculateOutput(float* inputs) const
	{
		float sum1 = 0.0f, sum2 = 0.0f;
		float inputMemberships[numberOfFuzzySets][numberOfInputs];
		for (unsigned int i = 0u; i != numberOfFuzzySets; ++i)
		{
			for (unsigned int j = 0u; j != numberOfInputs; ++j)
			{
				inputMemberships[i][j] = input_membership_functions[i][j](inputs[j]);
			}
		}

		for (unsigned int i = 0u; i != numberOfRules; ++i)
		{
			float values[numberOfInputs];
			for (unsigned int j = 0u; j != numberOfInputs; ++j)
			{
				unsigned char fuzzy_set = rules[i].input_fuzzy_set[j];
				values[j] = inputMemberships[fuzzy_set][j];
			}

			float weight = min_of(values, numberOfInputs);

			sum1 += weight * output_values[rules[i].out_fuzzy_set];
			sum2 += weight;
		}

		assert(fabs(sum2) > too_small_total_weight && "Too small values of sum2 give inaccurate results like NaN and inf. Please fix membership functions and/or "
			"combination of memberships and/or add more rules");

		return (sum1 / sum2);
	}
};

template<std::size_t numberOfInputs, std::size_t numberOfFuzzySets>
class FammForOptimization
{
	constexpr static float too_small_total_weight = 1e-6f;

	static constexpr std::size_t power(std::size_t base, std::size_t pow)
	{
		return pow == 0u ? 1u : base * power(base, pow - 1u);
	}

	template<class T, std::size_t sizeOfDimension, std::size_t numberOfDimensions>
	class NArray
	{
		constexpr static std::size_t mSize = power(sizeOfDimension, numberOfDimensions);
		T mData[mSize];

		template<class T2, std::size_t sizeOfDimension2, std::size_t numberOfDimensions2>
		class Indexer
		{
			T2* data;

			T& operator[](std::size_t index)
			{
				return Indexer<T2, sizeOfDimension2, numberOfDimensions2 - 1u>{ &data[index * power(sizeOfDimension2, numberOfDimensions2)] };
			}
		};

		template<class T2, std::size_t sizeOfDimension2>
		class Indexer<T2, sizeOfDimension2, 1u>
		{
			T2* data;

			T& operator[](std::size_t index)
			{
				return data[index];
			}
		};
	public:
		T& operator[](std::size_t index)
		{
			return Indexer<T, sizeOfDimension, numberOfDimensions>{ mData }[index];
		}

		const T& operator[](std::size_t index) const
		{
			return Indexer<const T, sizeOfDimension, numberOfDimensions>{ mData }[index];
		}

		T* flatten()
		{
			return mData;
		}

		const T* flatten() const
		{
			return mData;
		}
	};

	template<std::size_t numberOfInputs2, std::size_t currentInput = 0u>
	static typename std::enable_if<currentInput != numberOfInputs2, void>::type
		minWeightOfRule(float& weight, size_t ruleIndex, float input_membership_weights[][numberOfInputs2])
	{
		constexpr std::size_t sliceSize = power(numberOfFuzzySets, currentInput);
		std::size_t fuzzySetIndexInCurrentInput = (ruleIndex / sliceSize) % numberOfFuzzySets;
		if (input_membership_weights[fuzzySetIndexInCurrentInput][currentInput] < weight)
		{
			weight = input_membership_weights[fuzzySetIndexInCurrentInput][currentInput];
		}
	}

	template<std::size_t numberOfInputs2, std::size_t currentInput = 0u>
	static typename std::enable_if<currentInput == numberOfInputs2, void>::type
		minWeightOfRule(float& weight, std::size_t ruleIndex, float input_membership_weights[][numberOfInputs]) {}
public:
	constexpr static std::size_t number_of_rules = power(numberOfFuzzySets, numberOfInputs);
	NArray<float, numberOfFuzzySets, numberOfInputs> rules;
	TrapezoidFunction input_membership_functions[numberOfFuzzySets][numberOfInputs];

	float calculateOutput(float* inputs)
	{
		float inputMemberships[numberOfFuzzySets][numberOfInputs];
		for (unsigned int i = 0u; i != numberOfFuzzySets; ++i)
		{
			for (unsigned int j = 0u; j != numberOfInputs; ++j)
			{
				inputMemberships[i][j] = input_membership_functions[i][j](inputs[j]);
			}
		}

		float sum1 = 0.0f, sum2 = 0.0f;
		const float* const flattenedRules = rules.flatten();
		for (std::size_t i = 0u; i != number_of_rules; ++i)
		{
			float weight = 1.0f;
			minWeightOfRule<numberOfInputs>(weight, i, inputMemberships);
			sum1 += weight * flattenedRules[i];
			sum2 += weight;
		}

		if (fabs(sum2) <= too_small_total_weight) return 0.0f;

		return (sum1 / sum2);
	}
};

class FuzzySystemForOptimization
{
public:
	FammForOptimization<2u, 5u> famm;
	float inputWeights[4];

	float calculateOutput(float* inputs)
	{
		float inputsToFamm[2];
		inputsToFamm[0] = inputWeights[0] * inputs[in_theta] + inputWeights[1] * inputs[in_theta_dot];
		inputsToFamm[1] = inputWeights[2] * inputs[in_x] + inputWeights[3] * inputs[in_x_dot];
		return famm.calculateOutput(inputsToFamm);
	}

	template<class ErrorFunction>
	static void optimize(ErrorFunction& errorFunction, char* stateFileName)
	{
		constexpr static std::size_t numberOfTriesPerBest = 20u;
		constexpr static std::size_t numberOfSameBestToEnd = 10u;
		std::size_t lastBest = 0u;
		std::size_t numberOfSameBestInARow = 0u;
		constexpr float maxMutationStart = 0.25f;
		std::size_t generation = 1u;
		FuzzySystemForOptimization fuzzySystems[numberOfTriesPerBest];
		std::default_random_engine randomGenerator;
		std::ifstream inFile(stateFileName);
		auto rulesOldBest = fuzzySystems[lastBest].famm.rules.flatten();
		for (std::size_t i = 0u; i != 25u; ++i)
		{
			inFile >> rulesOldBest[i];
		}
		for (std::size_t j = 0u; j != 2u; ++j)
		{
			for (std::size_t i = 0u; i != 5u; ++i)
			{
				inFile >> fuzzySystems[lastBest].famm.input_membership_functions[i][j];
			}
		}
		for (std::size_t i = 0u; i != 4u; ++i)
		{
			inFile >> fuzzySystems[lastBest].inputWeights[i];
		}
		inFile.close();
		while (true)
		{
			std::cout << "Generation: " << generation << "\n";
			const float maxMutation = maxMutationStart / generation;
			std::uniform_real_distribution<float> distribution1(-maxMutation, maxMutation);
			std::uniform_real_distribution<float> distribution2(-maxMutation * 50.0f, maxMutation * 50.0f);
			for (std::size_t i = 0u; i != numberOfTriesPerBest; ++i)
			{
				if (i == lastBest) continue;
				auto rule1 = fuzzySystems[i].famm.rules.flatten();
				auto rules2 = fuzzySystems[lastBest].famm.rules.flatten();
				for (std::size_t j = 0u; j != 12u; ++j)
				{
					rule1[j] = rules2[j] + distribution2(randomGenerator);
					rule1[24u - j] = -rule1[j];
				}
				for (std::size_t j = 0u; j != 5u; ++j)
				{
					for (std::size_t k = 0u; k != 2u; ++k)
					{
						fuzzySystems[i].famm.input_membership_functions[j][k] = fuzzySystems[lastBest].famm.input_membership_functions[j][k];
					}
				}
				for (std::size_t j = 0u; j != 4u; ++j)
				{
					fuzzySystems[i].inputWeights[j] = fuzzySystems[lastBest].inputWeights[j] + distribution1(randomGenerator);
				}
				float input1Plus2 = fuzzySystems[i].inputWeights[0] + fuzzySystems[i].inputWeights[1];
				fuzzySystems[i].inputWeights[0] /= input1Plus2;
				fuzzySystems[i].inputWeights[1] /= input1Plus2;
				float input3Plus4 = fuzzySystems[i].inputWeights[2] + fuzzySystems[i].inputWeights[3];
				fuzzySystems[i].inputWeights[2] /= input3Plus4;
				fuzzySystems[i].inputWeights[3] /= input3Plus4;
			}
			float bestError = std::numeric_limits<float>::max();
			std::size_t bestIndex = 0u;
			for (std::size_t i = 0u; i != numberOfTriesPerBest; ++i)
			{
				const float error = errorFunction(fuzzySystems[i]);
				if (error < bestError)
				{
					bestError = error;
					bestIndex = i;
				}
			}
			if (bestIndex == lastBest)
			{
				++numberOfSameBestInARow;
				if (numberOfSameBestInARow == numberOfSameBestToEnd)
				{
					std::ofstream outFile(stateFileName);
					auto rulesNewBest = fuzzySystems[bestIndex].famm.rules.flatten();
					for (std::size_t i = 0u; i != 25u; ++i)
					{
						outFile << rulesNewBest[i] << ' ';
					}
					for (std::size_t j = 0u; j != 2u; ++j)
					{
						for (std::size_t i = 0u; i != 5u; ++i)
						{
							outFile << fuzzySystems[bestIndex].famm.input_membership_functions[i][j] << ' ';
						}
					}
					for (size_t i = 0u; i != 4u; ++i)
					{
						outFile << fuzzySystems[lastBest].inputWeights[i] << ' ';
					}
					outFile.close();
					return;
				}
			}
			else
			{
				lastBest = bestIndex;
				numberOfSameBestInARow = 0u;
			}

			++generation;
		}
	}
};

class FuzzySystem
{
	constexpr static unsigned int number_of_rules = 25u;

	Famm<number_of_combined_inputs, number_of_rules, number_of_input_regions, number_of_outputs> famm;

	void initFuzzyRules();
	void initMembershipFunctions();
public:
	FuzzySystem();
	~FuzzySystem() {}
	float calculateOutput(float* inputs) const;
};

#endif
