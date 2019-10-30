objects= lsh cube brute_force_points curve_projection_lsh curve_projection_hypercube curve_grid_lsh curve_grid_hypercube brute_force_curve
all:  $(objects)
lsh : Gmain.cpp
	c++ -std=c++11 -g -o lsh Gmain.cpp
cube: CubeMain.cpp
	c++ -std=c++11 -g -o cube CubeMain.cpp
brute_force_points: BruteForcePoints.cpp
	c++ -std=c++11  -g -o brute_force_points BruteForcePoints.cpp
curve_projection_lsh : Grid_Projection_Functions.o ProjectionLSH.o  arguments.o
	c++ -std=c++11 -g -o curve_projection_lsh  Grid_Projection_Functions.o ProjectionLSH.o arguments.o
curve_projection_hypercube : Grid_Projection_Functions.o ProjectionCube.o  arguments.o
	c++ -std=c++11 -g -o curve_projection_hypercube  Grid_Projection_Functions.o ProjectionCube.o arguments.o
curve_grid_lsh : Grid_Projection_Functions.o GridLSH.o  arguments.o
	c++ -std=c++11 -g -o curve_grid_lsh  Grid_Projection_Functions.o GridLSH.o arguments.o
brute_force_curve : Grid_Projection_Functions.o BruteForceCurve.o  arguments.o
		c++ -std=c++11 -g -o brute_force_curve  Grid_Projection_Functions.o BruteForceCurve.o arguments.o
curve_grid_hypercube : Grid_Projection_Functions.o GridCube.o  arguments.o
	c++ -std=c++11 -g -o curve_grid_hypercube  Grid_Projection_Functions.o GridCube.o arguments.o
GridCube.o : GridCube.cpp Grid_Projection_Functions.cpp arguments.cpp
	c++ -std=c++11 -g -c GridCube.cpp Grid_Projection_Functions.cpp arguments.cpp
ProjectionLSH.o : ProjectionLSH.cpp Grid_Projection_Functions.cpp arguments.cpp
	c++ -std=c++11 -g -c ProjectionLSH.cpp Grid_Projection_Functions.cpp arguments.cpp
ProjectionCube.o : ProjectionCube.cpp Grid_Projection_Functions.cpp arguments.cpp
	c++ -std=c++11 -g -c ProjectionCube.cpp Grid_Projection_Functions.cpp arguments.cpp
GridLSH.o : GridLSH.cpp Grid_Projection_Functions.cpp arguments.cpp
	c++ -std=c++11 -g -c GridLSH.cpp Grid_Projection_Functions.cpp arguments.cpp
Grid_Projection_Functions.o: Grid_Projection_Functions.cpp
	c++ -std=c++11 -g -c Grid_Projection_Functions.cpp
BruteForceCurve.o: BruteForceCurve.cpp Grid_Projection_Functions.cpp arguments.cpp
		c++ -std=c++11 -g -c BruteForceCurve.cpp Grid_Projection_Functions.cpp arguments.cpp
arguments.o: Grid_Projection_Functions.h
	c++ -std=c++11 -g -c arguments.cpp
CubeList.o: CubeList.h CubeList.cpp
	c++ -std=c++11 -g -c CubeList.cpp
clean :
	rm $(objects) *.o
