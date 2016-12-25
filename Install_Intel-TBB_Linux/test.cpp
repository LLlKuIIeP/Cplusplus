#include <tbb/tbb.h>
#include <tbb/parallel_for.h>

using namespace std;
using namespace tbb;

long long len = 5000;
float *set1 = new float[len];
float *set2 = new float[len];
float *set3 = new float[len];

int main() {
	parallel_for(blocked_range<size_t>(0, len, 100),
		[](const blocked_range<size_t>& r) {
			for( long i = r.begin(); i != r.end(); i++) {
				set3[i] = (set1[i] * set2[i]) / 2.0 + set2[i];
			}
		}
	);

return 0;
}
