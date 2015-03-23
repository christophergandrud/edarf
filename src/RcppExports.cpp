// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <RcppArmadillo.h>
#include <Rcpp.h>

using namespace Rcpp;

// wmean
double wmean(arma::rowvec x, arma::colvec w);
RcppExport SEXP edarf_wmean(SEXP xSEXP, SEXP wSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< arma::rowvec >::type x(xSEXP);
    Rcpp::traits::input_parameter< arma::colvec >::type w(wSEXP);
    __result = Rcpp::wrap(wmean(x, w));
    return __result;
END_RCPP
}
// vestl
arma::mat vestl(int n, int ntree, arma::mat pd_membership, arma::rowvec yvar, arma::mat inbag);
RcppExport SEXP edarf_vestl(SEXP nSEXP, SEXP ntreeSEXP, SEXP pd_membershipSEXP, SEXP yvarSEXP, SEXP inbagSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< int >::type n(nSEXP);
    Rcpp::traits::input_parameter< int >::type ntree(ntreeSEXP);
    Rcpp::traits::input_parameter< arma::mat >::type pd_membership(pd_membershipSEXP);
    Rcpp::traits::input_parameter< arma::rowvec >::type yvar(yvarSEXP);
    Rcpp::traits::input_parameter< arma::mat >::type inbag(inbagSEXP);
    __result = Rcpp::wrap(vestl(n, ntree, pd_membership, yvar, inbag));
    return __result;
END_RCPP
}
