ctmcForwardBackward <- function(ts, theta, obs) {
    .Call('_HMMRcpp_ctmcForwardBackward', PACKAGE = 'HMMRcpp', ts, theta, obs)
}

ctmcViterbi <- function(ts, theta, obs) {
    .Call('_HMMRcpp_ctmcViterbi', PACKAGE = 'HMMRcpp', ts, theta, obs)
}
