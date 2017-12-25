\name{HMMRcpp}
\alias{HMMRcpp}
\docType{package}
\title{
  Viterbi and ForwardBackward Implementation for Generic HMM
}
\description{
	This package focuses on implementing a generic Hidden Markov Model algorithm for a continuous-time Markov Chain hidden Markov models. It implements the Viterbi and Forward Backward algorithms in O(nm) time complexity. Each of the functions in this package require three inputs: ts, theta, and obs. ts is a timestamp vector of length m, theta is a double used to calculate the transition probability, and obs is an n x m likelihood matrix of P(observation | state).
}
\details{
	Key functions that are implemented in this package are ctmcViterbi and ctmcForwardBackward. See function documentation for more details.
}
\author{
Luke Puglisi - lpuglisi@umich.edu 
}

