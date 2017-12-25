\name{ctmcForwardBackward}
\alias{ctmcForwardBackward}
\docType{package}
\title{
Forward-Backward Algorithm Implemented in  Rcpp
}
\arguments{
	\item{ts}{size m numeric vector of timestamp values}
	\item{theta}{constant double value used to calculate the transition probability}
	\item{obs}{n x m matrix giving the probability of an observation given a certain state (e.g. P(Observation|State))}
}
\description{
This function implements the Forward-Backward algorithm of a generic HMM given a timestamp vector, constant theta, and an n x m observation matrix of P(Observation | State)
}
\usage{
ctmcForwardBackward(ts,theta,obs)	
}
\examples{
obs = matrix(c(0.88,0.10,0.88,0.10,0.02,0.30,0.02,0.30,0.10,0.60),2,5)
theta = log(2)
ts = c(1,2,3,4,5)
ctmcForwardBackward(ts,theta,obs)
}
