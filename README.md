![](https://travis-ci.org/zmjones/edarf.svg)

Functions useful for exploratory data analysis using random forests. Developed by [Zachary M. Jones](http://zmjones.com) and [Fridolin Linder](http://polisci.la.psu.edu/people/fjl128) in support of "[Exploratory Data Analysis Using Random Forests](https://github.com/zmjones/rfss/)."

This package allows you to easily calculate the partial dependence of an arbitrarily large set of explanatory variables on the outcome variable given a fitted random forest from the following packages (outcome variable types supported in parenthesis): [party](http://cran.r-project.org/web/packages/party/index.html) (multivariate, regression, and classification), [randomForestSRC](http://cran.r-project.org/web/packages/randomForestSRC/index.html) (regression, classification, and survival), and [randomForest](http://cran.r-project.org/web/packages/randomForest/index.html) (regression and classification).

`partial_dependence` can be run in parallel by registering the appropriate parallel backend using [doParallel](http://cran.r-project.org/web/packages/doParallel/index.html). Beyond the random forest and the set of variables for which to calculate the partial dependence, there are additional arguments which control the dimension of the prediction grid used (naturally, the more points used the longer execution will take) and whether or not points that were not observed in the data can be used in said grid (interpolation).

The `partial_dependence` method can also either return interactions (the partial dependence on unique combinations of a subset of the predictor space) or a list of bivariate partial dependence estimates.

For regression we provide (by default) confidence intervals using the bias-corrected infinitesimal jackknife ([Wager, Hastie, and Tibsharani, 2014](http://jmlr.org/papers/v15/wager14a.html)) using code adapted from [randomForestCI](https://github.com/swager/randomForestCI).

We also provide methods to extract and plot variable importance.

We are planning on adding methods to make interpreting proximity and maximal subtree matrices easier.

Pull requests, bug reports, feature requests, etc. are welcome!

## Contents

 - [Installation](#install)
 - [Partial Dependence](#partial_dependence)
    + [Classification](#classification)
    + [Regression](#regression)
	+ [Survival](#survival)
	+ [Multivariate](#multivariate)
 - [Variable Importance](#variable_importance)
	+ [Interaction Importance](#interaction_importance)
 - [Variance Estimation](#variance_estimation)
 - [Proximity Matrix Visualization](#proximity)

## <a name="install">Installation</a>

It is not yet on CRAN, but you can install it from Github using [devtools](http://cran.r-project.org/web/packages/devtools/index.html).

```{r}
library(devtools)
install_github("zmjones/edarf")
```

For many of the features in our package to be useable with [party](http://github.com/rforge/party) we require the use of our [forked copy](http://github.com/zmjones/party).

```{r}
install_github("zmjones/party", subdir = "pkg")
```

## <a name="partial_dependence">Partial Dependence</a>
### <a name="classification">Classification</a>

```{r}
library(edarf)
library(ggplot2)

data(iris)
library(randomForest)
fit <- randomForest(Species ~ ., iris)
pd <- partial_dependence(fit, df = iris, var = "Petal.Width", type = "prob")
plot_pd(pd, geom = "line")
ggsave("examples/iris_pd_line.png", width = 10, height = 5)
```
![](examples/iris_pd_line.png)

```{r}
plot_pd(pd, geom = "area")
ggsave("examples/iris_pd_area.png", width = 10, height = 5)
```
![](examples/iris_pd_area.png)

```{r}
pd <- partial_dependence(fit, df = iris, var = "Petal.Width")
plot_pd(pd, geom = "bar")
ggsave("examples/iris_pd_bar.png", width = 10, height = 5)
```
![](examples/iris_pd_bar.png)

```{r}
pd_int <- partial_dependence(fit, df = iris, var = c("Petal.Width", "Sepal.Length"),
                             interaction = TRUE, type = "prob")
plot_pd(pd_int, geom = "line", facet_var = "Petal.Width")
ggsave("examples/iris_pd_int_line.png", width = 10, height = 10)
```
![](examples/iris_pd_int_line.png)

```{r}
plot_pd(pd_int, geom = "area", facet_var = "Petal.Width")
ggsave("examples/iris_pd_int_area.png", width = 10, height = 10)
```
![](examples/iris_pd_int_area.png)

```{r}
pd_int <- partial_dependence(fit, df = iris, var = c("Petal.Width", "Sepal.Length"), interaction = TRUE)
plot_pd(pd_int, geom = "bar", facet_var = "Petal.Width")
ggsave("examples/iris_pd_int_bar.png", width = 10, height = 10)
```
![](examples/iris_pd_int_bar.png)

```{r}
pd_lst <- partial_dependence(fit, df = iris, var = c("Petal.Width", "Sepal.Length"),
                             interaction = FALSE, type = "prob")
plot_pd(pd_lst, geom = "line")
ggsave("examples/iris_pd_lst_line.png", width = 10, height = 5)
```
![](examples/iris_pd_lst_line.png)

### <a name="regression">Regression</a>

```{r}
data(swiss)
fit <- randomForest(Fertility ~ ., swiss, keep.inbag = TRUE)
pd <- partial_dependence(fit, df = swiss, var = "Education", ci = TRUE)
plot_pd(pd)
ggsave("examples/swiss_pd_line.png", width = 10, height = 5)
```
![](examples/swiss_pd_line.png)

```{r}
pd_int <- partial_dependence(fit, df = swiss, var = c("Education", "Catholic"), interaction = TRUE, ci = TRUE)
plot_pd(pd_int, facet_var = "Education")
ggsave("examples/swiss_pd_int_line.png", width = 10, height = 10)
```
![](examples/swiss_pd_int_line.png)

```{r}
pd_lst <- partial_dependence(fit, df = swiss, var = c("Education", "Catholic"), interaction = FALSE, ci = TRUE)
plot_pd(pd_lst)
ggsave("examples/swiss_pd_lst_line.png", width = 10, height = 5)
```
![](examples/swiss_pd_lst_line.png)

### <a name="survival">Survival</a>

```{r}
library(randomForestSRC)
data(veteran)
fit <- rfsrc(Surv(time, status) ~ ., veteran)
pd <- partial_dependence(fit, var = "age")
plot_pd(pd)
ggsave("examples/veteran_pd_line.png", width = 10, height = 5)
```
![](examples/veteran_pd_line.png)

```{r}
pd_int <- partial_dependence(fit, var = c("age", "diagtime"), interaction = TRUE)
plot_pd(pd_int, facet_var = "age")
ggsave("examples/veteran_pd_int_line.png", width = 10, height = 10)
```
![](examples/veteran_pd_int_line.png)

### <a name="multivariate">Multivariate</a>

```{r}
data(mtcars)
library(party)
fit <- cforest(hp + qsec ~ ., mtcars, controls = cforest_control(mtry = 2))
pd <- partial_dependence(fit, var = "mpg")
plot_pd(pd, scales = "free")
ggsave("examples/mtcars_pd_line.png", width = 10, height = 5)
```
![](examples/mtcars_pd_line.png)

Multivariate two-way interaction plots not yet implemented. See [Issue #19](https://github.com/zmjones/edarf/issues/19).

## <a name="variable_importance">Variable Importance</a>

```{r}
fit <- randomForest(Species ~ ., iris)
imp <- variable_importance(fit, var = colnames(iris)[-5], type = "aggregate", data = iris)
plot_imp(imp, geom = "bar")
ggsave("examples/iris_imp.png", width = 10, height = 5)
```
![](examples/iris_imp.png)

```{r}
imp <- variable_importance(fit, var = colnames(iris)[-5], type = "local", data = iris)
plot_imp(imp, geom = "bar")
ggsave("examples/iris_imp_class.png", width = 10, height = 5)
```
![](examples/iris_imp_class.png)

```{r}
fit <- randomForest(Fertility ~ ., swiss)
imp <- variable_importance(fit, var = colnames(swiss)[-1], type = "aggregate", data = swiss)
plot_imp(imp)
ggsave("examples/swiss_imp.png", width = 10, height = 5)
```
![](examples/swiss_imp.png)

```{r}
imp <- variable_importance(fit, var = colnames(swiss)[-1], type = "local", data = swiss)
plot_imp(imp, xlab = "Fertility")
ggsave("examples/swiss_imp_local.png", width = 10, height = 5)
```
![](examples/swiss_imp_local.png)

### <a name="interaction_importance">Interaction Importance</a>

```{r}
int <- variable_importance(fit, var = c("Education", "Catholic"), type = "aggregate", interaction = TRUE,
                           data = swiss)
plot_imp(int, geom = "bar")
ggsave("examples/iris_int_imp.png", width = 10, height = 5)
```
![](examples/iris_int_imp.png)

```{r}
int <- variable_importance(fit, var = c("Education", "Catholic"), type = "local", interaction = TRUE,
                           data = swiss)
plot_imp(int, xlab = "Fertility")
ggsave("examples/iris_int_imp_local.png", width = 7, height = 7)
```
![](examples/iris_int_imp_local.png)

## <a name="variance_estimation">Variance Estimation</a>

To use `var_est` with `randomForest` we need an updated (but not merged) version of [`randomForest`]([randomForest](http://github.com/swager/randomForest)) which is installed below with `devtools`.

```{r}
library(devtools)
install_github("swager/randomForest")

fit <- randomForest(hp ~ ., mtcars, keep.inbag = TRUE)
out <- var_est(fit, mtcars)
```

All the below is handled internally if variance estimates are requested, for `partial_dependence`, however, it is possible to use `var_est` with the fitted model alone as well (regression with `randomForest`, `cforest`, and `rfsrc`)

```{r}
plot_pred(out$prediction, mtcars$hp, out$variance,
          outlier_idx = which(rank(out$prediction - mtcars$hp) %in% 1:5), labs = row.names(out),
          xlab = "Observed Horsepower", ylab = "Predicted Horsepower")
ggsave("examples/mtcars_pred.png", width = 10, height = 5)
```
![](examples/mtcars_pred.png)

## <a name="proximity">Proximity Matrix Visualization</a>

```{r}
fit <- randomForest(hp ~ ., mtcars, proximity = TRUE)
prox <- extract_proximity(fit)
pca <- prcomp(prox)
plot_prox(pca, labels = row.names(mtcars),
          color = as.factor(mtcars$cyl), color_label = "# cylinders",
          alpha = mtcars$mpg, alpha_label = "mpg")
ggsave("examples/mtcars_prox.png", width = 10, height = 7.5)
```
![](examples/mtcars_prox.png)

```{r}
fit <- randomForest(Species ~ ., iris, proximity = TRUE)
prox <- extract_proximity(fit)
pca <- prcomp(prox)
plot_prox(pca,
          color = iris$Species, color_label = "Species",
          size = iris$Petal.Length, size_label = "Petal Length",
          alpha = iris$Petal.Width, alpha_label = "Petal Width")
ggsave("examples/iris_prox.png", width = 10, height = 7.5)
```

![](examples/iris_prox.png)
