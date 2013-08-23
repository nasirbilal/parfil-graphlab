#include <cmath>
#include <memory>
#include <vector>
#include <parfil/robot.h>
#include <parfil/filter.h>

void TestCase1(std::vector<parfil::Motion>& motions, std::vector<parfil::Measurement>& measurements) {
  // fill in motions
  int num_motions = 8;
  motions.resize(num_motions);
  for (int i=0; i<num_motions; ++i) {
    motions[i].steering_angle = 2.0*M_PI/10.0;
    motions[i].forward_distance = 20.0;
  }

  // fill in measurements
  double[] measurements_arr = {
      4.746936, 3.859782, 3.045217, 2.045506,
      3.510067, 2.916300, 2.146394, 1.598332,
      2.972469, 2.407489, 1.588474, 1.611094,
      1.906178, 1.193329, 0.619356, 0.807930,
      1.352825, 0.662233, 0.144927, 0.799090,
      0.856150, 0.214590, 5.651497, 1.062401,
      0.194460, 5.660382, 4.761072, 2.471682,
      5.717342, 4.736780, 3.909599, 2.342536
  };
  int num_measurements = 8;
  int measurement_dimension = 4;
  measurements.resize(8);
  for (int i=0; i<num_measurements; ++i) {
    measurements[i].resize(measurement_dimension);
    double* from = measurements_arr + measurement_dimension*i;
    double* to = from + measurement_dimension;
    measurements[i].assign(from,to);
  }
}

int main(int, char**) {
  int num_particles = 500;
  std::unique_ptr<parfil::Filter> filter(new parfil::Filter(num_particles));

  std::vector<parfil::Motion> motions;
  std::vector<parfil::Measurement> measurements;
  TestCase1(motions,measurements);

  filter->run(motions,measurements);

  double x,y,heading;
  filter->GetPose(x,y,heading);
  std::cout << "x: " << x << " y: " << y << " heading: " << heading << std::endl;

  return 0;
}
