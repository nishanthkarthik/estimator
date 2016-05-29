# finite difference estimator

# `pycomp.sh`

## Pure python for computing and plotting

- 370x370 grid
- 300 iterations
- *1m 25.584s* for python interpreter

# `baremetal.sh`

## Python for plotting and C for computation

- 370x370 grid
- 100,000 iterations
- *1m 32.249s* for python + gcc + C
- *1m 0.165s* after tuning `C` code, thanks to http://stackoverflow.com/a/37506654/3951920
- *0m 59.983s* after tuning types and removing branches
