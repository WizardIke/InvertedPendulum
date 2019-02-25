#include "../Assignment2_159302/fuzzylogic.h"
#include "../Assignment2_159302/WorldState.h"

class ErrorFunction
{
	struct TestCase
	{
		float x;
		float theta;
	};
	TestCase testCases[143] =
	{
		{ -2.5f, -1.5f },
		{ -2.5f, -1.25f },
		{ -2.5f, -1.0f },
		{ -2.5f, -0.75f },
		{ -2.5f, -0.5f },
		{ -2.5f, -0.25f },
		{ -2.5f, 0.0f },
		{ -2.5f, 0.25f },
		{ -2.5f, 0.5f },
		{ -2.5f, 0.75f },
		{ -2.5f, 1.0f },
		{ -2.5f, 1.25f },
		{ -2.5f, 1.5f },

		{ -2.0f, -1.5f },
		{ -2.0f, -1.25f },
		{ -2.0f, -1.0f },
		{ -2.0f, -0.75f },
		{ -2.0f, -0.5f },
		{ -2.0f, -0.25f },
		{ -2.0f, 0.0f },
		{ -2.0f, 0.25f },
		{ -2.0f, 0.5f },
		{ -2.0f, 0.75f },
		{ -2.0f, 1.0f },
		{ -2.0f, 1.25f },
		{ -2.0f, 1.5f },

		{ -1.5f, -1.5f },
		{ -1.5f, -1.25f },
		{ -1.5f, -1.0f },
		{ -1.5f, -0.75f },
		{ -1.5f, -0.5f },
		{ -1.5f, -0.25f },
		{ -1.5f, 0.0f },
		{ -1.5f, 0.25f },
		{ -1.5f, 0.5f },
		{ -1.5f, 0.75f },
		{ -1.5f, 1.0f },
		{ -1.5f, 1.25f },
		{ -1.5f, 1.5f },

		{ -1.0f, -1.5f },
		{ -1.0f, -1.25f },
		{ -1.0f, -1.0f },
		{ -1.0f, -0.75f },
		{ -1.0f, -0.5f },
		{ -1.0f, -0.25f },
		{ -1.0f, 0.0f },
		{ -1.0f, 0.25f },
		{ -1.0f, 0.5f },
		{ -1.0f, 0.75f },
		{ -1.0f, 1.0f },
		{ -1.0f, 1.25f },
		{ -1.0f, 1.5f },

		{ -0.5f, -1.5f },
		{ -0.5f, -1.25f },
		{ -0.5f, -1.0f },
		{ -0.5f, -0.75f },
		{ -0.5f, -0.5f },
		{ -0.5f, -0.25f },
		{ -0.5f, 0.0f },
		{ -0.5f, 0.25f },
		{ -0.5f, 0.5f },
		{ -0.5f, 0.75f },
		{ -0.5f, 1.0f },
		{ -0.5f, 1.25f },
		{ -0.5f, 1.5f },

		{ 0.0f, -1.5f },
		{ 0.0f, -1.25f },
		{ 0.0f, -1.0f },
		{ 0.0f, -0.75f },
		{ 0.0f, -0.5f },
		{ 0.0f, -0.25f },
		{ 0.0f, 0.0f },
		{ 0.0f, 0.25f },
		{ 0.0f, 0.5f },
		{ 0.0f, 0.75f },
		{ 0.0f, 1.0f },
		{ 0.0f, 1.25f },
		{ 0.0f, 1.5f },

		{ 0.5f, -1.5f },
		{ 0.5f, -1.25f },
		{ 0.5f, -1.0f },
		{ 0.5f, -0.75f },
		{ 0.5f, -0.5f },
		{ 0.5f, -0.25f },
		{ 0.5f, 0.0f },
		{ 0.5f, 0.25f },
		{ 0.5f, 0.5f },
		{ 0.5f, 0.75f },
		{ 0.5f, 1.0f },
		{ 0.5f, 1.25f },
		{ 0.5f, 1.5f },

		{ 1.0f, -1.5f },
		{ 1.0f, -1.25f },
		{ 1.0f, -1.0f },
		{ 1.0f, -0.75f },
		{ 1.0f, -0.5f },
		{ 1.0f, -0.25f },
		{ 1.0f, 0.0f },
		{ 1.0f, 0.25f },
		{ 1.0f, 0.5f },
		{ 1.0f, 0.75f },
		{ 1.0f, 1.0f },
		{ 1.0f, 1.25f },
		{ 1.0f, 1.5f },

		{ 1.5f, -1.5f },
		{ 1.5f, -1.25f },
		{ 1.5f, -1.0f },
		{ 1.5f, -0.75f },
		{ 1.5f, -0.5f },
		{ 1.5f, -0.25f },
		{ 1.5f, 0.0f },
		{ 1.5f, 0.25f },
		{ 1.5f, 0.5f },
		{ 1.5f, 0.75f },
		{ 1.5f, 1.0f },
		{ 1.5f, 1.25f },
		{ 1.5f, 1.5f },

		{ 2.0f, -1.5f },
		{ 2.0f, -1.25f },
		{ 2.0f, -1.0f },
		{ 2.0f, -0.75f },
		{ 2.0f, -0.5f },
		{ 2.0f, -0.25f },
		{ 2.0f, 0.0f },
		{ 2.0f, 0.25f },
		{ 2.0f, 0.5f },
		{ 2.0f, 0.75f },
		{ 2.0f, 1.0f },
		{ 2.0f, 1.25f },
		{ 2.0f, 1.5f },

		{ 2.5f, -1.5f },
		{ 2.5f, -1.25f },
		{ 2.5f, -1.0f },
		{ 2.5f, -0.75f },
		{ 2.5f, -0.5f },
		{ 2.5f, -0.25f },
		{ 2.5f, 0.0f },
		{ 2.5f, 0.25f },
		{ 2.5f, 0.5f },
		{ 2.5f, 0.75f },
		{ 2.5f, 1.0f },
		{ 2.5f, 1.25f },
		{ 2.5f, 1.5f }
	};

	static float runTestCase(const TestCase testCase, FuzzySystemForOptimization& fuzzySystem)
	{
		float inputs[4];
		WorldStateType prevState, newState;
		float const h = 0.002f;
		prevState.init();
		newState.init();
		prevState.angle = testCase.theta;
		prevState.x = testCase.x;

		float error = 0.0f;
		for (size_t i = 0u; i != 10000; ++i)
		{
			inputs[in_theta] = prevState.angle;
			inputs[in_theta_dot] = prevState.angle_dot;
			inputs[in_x] = prevState.x;
			inputs[in_x_dot] = prevState.x_dot;

			prevState.F = fuzzySystem.calculateOutput(inputs); //call the fuzzy controller

			newState.angle_double_dot = calc_angular_acceleration(prevState);
			newState.angle_dot = prevState.angle_dot + (h * newState.angle_double_dot);
			newState.angle = prevState.angle + (h * newState.angle_dot);
			if (newState.angle > 3.14159265359f)
			{
				newState.angle -= 2 * 3.14159265359f;
			}
			else if (newState.angle < -3.14159265359f)
			{
				newState.angle += 2 * 3.14159265359f;
			}
			newState.F = prevState.F;
			newState.x_double_dot = calc_horizontal_acceleration(prevState);
			newState.x_dot = prevState.x_dot + (h * newState.x_double_dot);
			newState.x = prevState.x + (h * newState.x_dot);

			prevState.x = newState.x;
			prevState.angle = newState.angle;
			prevState.x_dot = newState.x_dot;
			prevState.angle_dot = newState.angle_dot;
			prevState.angle_double_dot = newState.angle_double_dot;
			prevState.x_double_dot = newState.x_double_dot;

			error += std::sqrt(abs(newState.x));
			error += std::sqrt(abs(newState.angle));
		}
		return error;
	}
public:
	float operator()(FuzzySystemForOptimization& fuzzySystem)
	{
		float error = 0.0f;
		for (const TestCase& testCase : testCases)
		{
			error += runTestCase(testCase, fuzzySystem);
		}
		return error;
	}
};

int main()
{
	initPendulumWorld();
	ErrorFunction ef;
	FuzzySystemForOptimization::optimize(ef, "solution.txt");
}