% Generated by roxygen2 (4.1.1): do not edit by hand
% Please edit documentation in R/plot.R
\name{plot_pd}
\alias{plot_pd}
\title{Plot partial dependence from random forests}
\usage{
plot_pd(pd, geom = "line", xlab = NULL, ylab = NULL, title = "",
  facet_var = NULL, scales = "free_x")
}
\arguments{
\item{pd}{object of class \code{c("pd", "data.frame")} as returned by
\code{\link{partial_dependence}}}

\item{geom}{character describing type of plot desired: "bar", "line", or "area"}

\item{xlab}{x-axis label, default depends on input}

\item{ylab}{y-axis label, default depends on input}

\item{title}{title for the plot}

\item{facet_var}{a character vector indicating the variable that should be used
to facet on if interaction is plotted. If not specified the variable with less
unique values is chosen.}

\item{scales}{can be "free", "free_x", "free_y" or "fixed", applicable when facetting}
}
\value{
a ggplot2 object
}
\description{
Plot partial dependence from random forests
}
\examples{
\dontrun{
library(randomForest)
library(edarf)
data(iris)
fit <- randomForest(Species ~ ., iris)
pd <- partial_dependence(fit, iris, "Petal.Width", type = "prob")
plot_pd(pd, geom = "area")
}
}

