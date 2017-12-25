
#include <Rcpp.h>
using namespace std;
using namespace Rcpp;

// [[Rcpp::export]]
IntegerVector ctmcViterbi(NumericVector ts, double theta, NumericMatrix obs) {
  int m = (int)ts.size(); //sequence length
  int n = (int)obs.nrow(); //number of states
  double n2 = obs.nrow();
  double ml = -1;
  double match;
  double mismatch;
  double v;
  double v1;
  double v2;
  NumericMatrix delta(n, m);
  NumericMatrix result(2, m);
  IntegerMatrix phi(n, m);
  IntegerVector viterbiPath(m);
  NumericVector pi(n);
  double tmp = (1/n2);
  std::fill(result.begin(), result.end(), -1);
  std::fill(delta.begin(), delta.end(), -1);
  std::fill(pi.begin(), pi.end(), tmp);
  if ( obs.ncol() != m ) {
    stop("The input matrix does not conform to the other parameters");
  }
  //Modified viterbi algorithm - Storing previous highest probability and state
  for(int i=0; i < n; ++i) {
    delta(i,0) = pi(i) * obs(i, 0);
    if (delta(i,0) > result(0,0)) {
      result(0,0) = delta(i,0);
      result(1,0) = i;
    }
  }
  for(int t=1; t < m; ++t) {
    match =  1.0 - (((n2-1)/n2)*(1.0 - exp(-1*theta*(ts[t] - ts[t-1]))));
    mismatch = (1/n2) * (1.0 - exp(-1*theta*(ts[t] - ts[t-1])));
    for(int i=0; i < n; ++i) {
      v = (i==result(1,t-1)) ? delta(i,t-1)*match*obs(i, t) : max(delta(result(1,t-1),t-1)*mismatch*obs(i, t),delta(i,t-1)*match*obs(i, t));
      v1 = (i==result(1,t-1)) ? 1 : 0;
      v2 = (delta(result(1,t-1),t-1)*mismatch*obs(i, t) > delta(i,t-1)*match*obs(i, t)) ? 1:0;
      if (v > delta(i,t)) {
        delta(i,t) = v;
        if (v1 == 1) {
          phi(i,t) = i;
        }
        else if (v2==1) {
          phi(i,t) = result(1,t-1);
        }
        else {
          phi(i,t) = i;
        }
        if (delta(i,t) > result(0,t)) {
          result(0,t) = delta(i,t);
          result(1,t) = i;
        }
      }
    }
  }
  //Go through states to find optimal path
  for(int i=0; i < n; ++i) {
    if ( ml < delta(i,m-1) ) {
      ml = delta(i,m-1);
      viterbiPath[m-1] = i;
    }
  }
  for(int i=m-1; i > 0; --i) {
    viterbiPath[i-1] = phi(viterbiPath[i],i);
  }
  return viterbiPath;
}
