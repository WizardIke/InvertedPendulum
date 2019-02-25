#include <algorithm>
#include <cassert>
#include "fuzzylogic.h"

using namespace std;

/////////////////////////////////////////////////////////////////

void FuzzySystem::initFuzzyRules()
{
	famm.rules[0].input_fuzzy_set[in_theta_combined] = in_nl;
	famm.rules[0].input_fuzzy_set[in_x_combined] = in_nl;
	famm.rules[1].input_fuzzy_set[in_theta_combined] = in_ns;
	famm.rules[1].input_fuzzy_set[in_x_combined] = in_nl;
	famm.rules[2].input_fuzzy_set[in_theta_combined] = in_ze;
	famm.rules[2].input_fuzzy_set[in_x_combined] = in_nl;
	famm.rules[3].input_fuzzy_set[in_theta_combined] = in_ps;
	famm.rules[3].input_fuzzy_set[in_x_combined] = in_nl;
	famm.rules[4].input_fuzzy_set[in_theta_combined] = in_pl;
	famm.rules[4].input_fuzzy_set[in_x_combined] = in_nl;

	famm.rules[5].input_fuzzy_set[in_theta_combined] = in_nl;
	famm.rules[5].input_fuzzy_set[in_x_combined] = in_ns;
	famm.rules[6].input_fuzzy_set[in_theta_combined] = in_ns;
	famm.rules[6].input_fuzzy_set[in_x_combined] = in_ns;
	famm.rules[7].input_fuzzy_set[in_theta_combined] = in_ze;
	famm.rules[7].input_fuzzy_set[in_x_combined] = in_ns;
	famm.rules[8].input_fuzzy_set[in_theta_combined] = in_ps;
	famm.rules[8].input_fuzzy_set[in_x_combined] = in_ns;
	famm.rules[9].input_fuzzy_set[in_theta_combined] = in_pl;
	famm.rules[9].input_fuzzy_set[in_x_combined] = in_ns;

	famm.rules[10].input_fuzzy_set[in_theta_combined] = in_nl;
	famm.rules[10].input_fuzzy_set[in_x_combined] = in_ze;
	famm.rules[11].input_fuzzy_set[in_theta_combined] = in_ns;
	famm.rules[11].input_fuzzy_set[in_x_combined] = in_ze;
	famm.rules[12].input_fuzzy_set[in_theta_combined] = in_ze;
	famm.rules[12].input_fuzzy_set[in_x_combined] = in_ze;
	famm.rules[13].input_fuzzy_set[in_theta_combined] = in_ps;
	famm.rules[13].input_fuzzy_set[in_x_combined] = in_ze;
	famm.rules[14].input_fuzzy_set[in_theta_combined] = in_pl;
	famm.rules[14].input_fuzzy_set[in_x_combined] = in_ze;

	famm.rules[15].input_fuzzy_set[in_theta_combined] = in_nl;
	famm.rules[15].input_fuzzy_set[in_x_combined] = in_ps;
	famm.rules[16].input_fuzzy_set[in_theta_combined] = in_ns;
	famm.rules[16].input_fuzzy_set[in_x_combined] = in_ps;
	famm.rules[17].input_fuzzy_set[in_theta_combined] = in_ze;
	famm.rules[17].input_fuzzy_set[in_x_combined] = in_ps;
	famm.rules[18].input_fuzzy_set[in_theta_combined] = in_ps;
	famm.rules[18].input_fuzzy_set[in_x_combined] = in_ps;
	famm.rules[19].input_fuzzy_set[in_theta_combined] = in_pl;
	famm.rules[19].input_fuzzy_set[in_x_combined] = in_ps;

	famm.rules[20].input_fuzzy_set[in_theta_combined] = in_nl;
	famm.rules[20].input_fuzzy_set[in_x_combined] = in_pl;
	famm.rules[21].input_fuzzy_set[in_theta_combined] = in_ns;
	famm.rules[21].input_fuzzy_set[in_x_combined] = in_pl;
	famm.rules[22].input_fuzzy_set[in_theta_combined] = in_ze;
	famm.rules[22].input_fuzzy_set[in_x_combined] = in_pl;
	famm.rules[23].input_fuzzy_set[in_theta_combined] = in_ps;
	famm.rules[23].input_fuzzy_set[in_x_combined] = in_pl;
	famm.rules[24].input_fuzzy_set[in_theta_combined] = in_pl;
	famm.rules[24].input_fuzzy_set[in_x_combined] = in_pl;

	famm.rules[0].out_fuzzy_set = out_ns;
	famm.rules[1].out_fuzzy_set = out_nl;
	famm.rules[2].out_fuzzy_set = out_nm;
	famm.rules[3].out_fuzzy_set = out_pvvl;
	famm.rules[4].out_fuzzy_set = out_pl;

	famm.rules[5].out_fuzzy_set = out_nvs;
	famm.rules[6].out_fuzzy_set = out_nl;
	famm.rules[7].out_fuzzy_set = out_nvvl;
	famm.rules[8].out_fuzzy_set = out_pvvl;
	famm.rules[9].out_fuzzy_set = out_pm;

	famm.rules[10].out_fuzzy_set = out_nvl;
	famm.rules[11].out_fuzzy_set = out_nvl;
	famm.rules[12].out_fuzzy_set = out_ze;
	famm.rules[13].out_fuzzy_set = out_pvl;
	famm.rules[14].out_fuzzy_set = out_pvl;

	famm.rules[15].out_fuzzy_set = out_nm;
	famm.rules[16].out_fuzzy_set = out_nvvl;
	famm.rules[17].out_fuzzy_set = out_pvvl;
	famm.rules[18].out_fuzzy_set = out_pl;
	famm.rules[19].out_fuzzy_set = out_pvs;

	famm.rules[20].out_fuzzy_set = out_nl;
	famm.rules[21].out_fuzzy_set = out_nvvl;
	famm.rules[22].out_fuzzy_set = out_pm;
	famm.rules[23].out_fuzzy_set = out_pl;
	famm.rules[24].out_fuzzy_set = out_ps;
}


void FuzzySystem::initMembershipFunctions() 
{
	famm.input_membership_functions[in_nl][in_theta_combined] = TrapezoidFunction(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), -1.5f, -1.0f);
	famm.input_membership_functions[in_ns][in_theta_combined] = TrapezoidFunction(-1.5f, -1.0f, -0.5f, -0.0f);
	famm.input_membership_functions[in_ze][in_theta_combined] = TrapezoidFunction(-1.0f, -0.0f, 0.0f, 1.0f);
	famm.input_membership_functions[in_ps][in_theta_combined] = TrapezoidFunction(0.0f, 0.5f, 1.0f, 1.5f);
	famm.input_membership_functions[in_pl][in_theta_combined] = TrapezoidFunction(1.0f, 1.5f, std::numeric_limits<float>::max(), std::numeric_limits<float>::max());

	famm.input_membership_functions[in_nl][in_x_combined] = TrapezoidFunction(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), -2.0f, -1.5f);
	famm.input_membership_functions[in_ns][in_x_combined] = TrapezoidFunction(-2.0f, -1.5f, -1.0f, -0.0f);
	famm.input_membership_functions[in_ze][in_x_combined] = TrapezoidFunction(-1.0f, -0.5f, 0.5f, 1.0f);
	famm.input_membership_functions[in_ps][in_x_combined] = TrapezoidFunction(0.0f, 1.0f, 1.5f, 2.0f);
	famm.input_membership_functions[in_pl][in_x_combined] = TrapezoidFunction(1.5f, 2.0f, std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
}

FuzzySystem::FuzzySystem()
{
	famm.output_values[out_nvvl] = -114.0f;
	famm.output_values[out_nvl] = -104.0f;
	famm.output_values[out_nl] = -95.0f;
	famm.output_values[out_nm] = -91.0f;
	famm.output_values[out_ns] = -80.0f;
	famm.output_values[out_nvs] = -71.0f;
	famm.output_values[out_ze] = 0.0f;
	famm.output_values[out_pvs] = 71.0f;
	famm.output_values[out_ps] = 80.0f;
	famm.output_values[out_pm] = 91.0f;
	famm.output_values[out_pl] = 95.0f;
	famm.output_values[out_pvl] = 104.0f;
	famm.output_values[out_pvvl] = 114.0f;

	initFuzzyRules();
	initMembershipFunctions();
}

//////////////////////////////////////////////////////////////////////////////

TrapezoidFunction::TrapezoidFunction(float x1, float x2, float x3, float x4)
{
	a = x1;
	b = x2;
	c = x3;
	d = x4;
	l_slope = 1.0f / (b - a);
	r_slope = 1.0f / (c - d);
}

   //////////////////////////////////////////////////////////////////////////////


   //////////////////////////////////////////////////////////////////////////////
float TrapezoidFunction::operator()(float x) const
{
	if ((x <= a) || (x >= d))
		return 0.0f;
	if (x <= b)
		return l_slope * (x - a);
	if (x >= c)
		return  r_slope * (x - d);
	return 1.0f;
}

   //////////////////////////////////////////////////////////////////////////////
float min_of(float values[], unsigned int no_of_inputs) 
{
	float val = values[0];
	for (unsigned int i = 1u; i != no_of_inputs; ++i) {
		if (values[i] < val)
			val = values[i];
	}
	return val;
}



//////////////////////////////////////////////////////////////////////////////
float FuzzySystem::calculateOutput(float* inputs) const
{
	float inputsToFamm[number_of_combined_inputs];
	inputsToFamm[in_theta_combined] = 0.8f * inputs[in_theta] + 0.2f * inputs[in_theta_dot];
	inputsToFamm[1] = 0.53907f * inputs[in_x] + 0.46093f * inputs[in_x_dot];
	return famm.calculateOutput(inputsToFamm);
}