
#include <Rcpp.h>
using namespace std;
using namespace Rcpp;

// [[Rcpp::export]]
NumericMatrix ctmcForwardBackward(NumericVector ts, double theta, NumericMatrix obs) {
  int m = (int)ts.size();
  int n = (int)obs.nrow();
  double tot;
  double cons;
  NumericVector pi(n);
  NumericMatrix alpha(n, m);
  NumericMatrix beta(n, m);
  NumericMatrix condProb(n,m);
  double n2= obs.nrow();
  double tmp = (1/n2);
  std::fill(pi.begin(), pi.end(), tmp);
  if ( obs.ncol() != m ) {
    stop("The input matrix does not conform to the other parameters");
  }
  //Calculate alpha for the forward loop
  for(int i=0; i < n; ++i) {
    alpha(i,0) = pi(i) * obs(i,0);
  }
  for(int t=1; t < m; ++t) {
    cons = (1.0 - exp(-1*theta*(ts[t] - ts[t-1])));
    tot = 0;
    for(int i=0; i < n; ++i) {
      tot += alpha(i,t-1);
    }
    for (int i=0; i<n; ++i) {
      alpha(i,t) = ((cons/n2)*tot + alpha(i,t-1)*(1-cons))*obs(i, t);
    }
  }
  //Calulate beta for the backward forwardLoop
  for(int i=0; i < n; ++i) {
    beta(i,m-1) = 1;
  }
  for(int t=m-2; t >=0; --t) {
    cons = (1.0 - exp(-1*theta*(ts[t+1] - ts[t])));
    tot = 0;
    for(int i=0; i < n; ++i) {
      tot += (cons/n2) * beta(i,t+1) * obs(i,t+1);
    }
    for (int i=0; i<n; ++i) {
      beta(i,t) = tot + beta(i,t+1)*obs(i,t+1)*(1-cons);
    }
  }
  //Calculating probabilities across states and t
  for(int t=0; t < m; ++t) {
    double sum = 0;
    for(int i=0; i < n; ++i) {
      sum += (alpha(i,t) * beta(i,t));
    }
    for(int i=0; i < n; ++i) {
      condProb(i,t) = (alpha(i,t) * beta(i,t)) / sum;
    }
  }
  return condProb;
}
