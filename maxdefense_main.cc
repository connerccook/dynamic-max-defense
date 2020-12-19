
#include "timer.hh"
#include "maxdefense.hh"

void dp(const ArmorVector& armors, int total_cost){
	const int n = armors.size();
	const int W = total_cost;
	
	std::vector<std::vector<double>> T;
	std::vector<double> X;
	std::vector<double> V;
	size_t i,j;
	for(i = 0; i <= n; i++){
		T.push_back(std::vector<double>());
		for(j = 0; j <= W; j++){
			T[i].push_back(0.0);
		}
	}

	for(auto armor : armors){
		X.push_back(armor->cost());
		V.push_back(armor->defense());
	}
	for(i = 1; i <= n; i++){
		for (j = 1; j <= W; j++){
			T[i][j] = std::numeric_limits<double>::min(); 
		}
	}


	for(i = 1; i <= n; i++){
		for(j = 0; j <= W; j++){
			if(X[i-1] <= j){
				T[i][j]=std::max(T[i-1][j],V[i-1]+T[i-1][j-X[i-1]]);
			} else {
				T[i][j]=T[i-1][j];
			}
		}
	}
	
	std::cout << T[n][W] << std::endl;
}

int main()
{
	auto all_armors = load_armor_database("armor.csv");
	assert( all_armors );
	auto filtered_armors = filter_armor_vector(*all_armors, 1, 2500, 6);
	Timer timer;
	//soln_greedy = greedy_max_defense(*filtered_armors, 1000);
	dp(*filtered_armors,1000);
	double elapsed = timer.elapsed();
	std::cout << "Elapsed: " << elapsed << std::endl;
	return 0;
}


