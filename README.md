# Assignment 1: - Subdivision curves

##  MA: Tessellated quadratic and cubic B-splines: 
The logic of quadratic and cubic b-spline is implemented in Tessellation Evaluation Shader. To define if we have to run quadratic or cubic b-splines, manual changes are required in the TCS (output layout = n)and TES file(type = 4 or 5). The TCS and TES file has proper documentation about this.


The image given below has GPU tessellation with # of Isolines = 52 for Pentagon shape:

![abc](https://github.com/Rohit8y/subDivisionSplines/blob/main/TS_Pent.png?raw=true)


The image given below has GPU tessellation with # of Isolines = 10 for Basis shape:

![abc](https://github.com/Rohit8y/subDivisionSplines/blob/main/TS_basis.png?raw=true)


And, the image given below has GPU tessellation with # of Isolines = 20 for G shape:

![abc](https://github.com/Rohit8y/subDivisionSplines/blob/main/TS_G.png?raw=true)

## MA: General curve subdivision on CPU:
The "CPU Subdivision" checkbox in the UI generates subdivison for the given shape. The "subdivision steps" value increase the subdivision steps, resulting in higher number of control points. The mask value can be changed from the UI option as well.

The image given below has has subdivision for mask 14641, with subdivision steps = 4 for shape Pentagon
![abc](https://github.com/Rohit8y/subDivisionSplines/blob/main/subDiv_Pent_default.png?raw=true)
And, the image given below has has subdivision for mask 14641, with subdivision steps = 2  for shape Basis
![abc](https://github.com/Rohit8y/subDivisionSplines/blob/main/subDiv_Basis_defauult.png?raw=true)
And, the image given below has has subdivision for mask 14641, with subdivision steps = 8  for shape G
![abc](https://github.com/Rohit8y/subDivisionSplines/blob/main/subDic_G_default.png?raw=true)
When we change the mask to 1331 for shape Basis with subdiv steps: 5 , we get 
![abc](https://github.com/Rohit8y/subDivisionSplines/blob/main/subDiv_basis_1331.png?raw=true)

## MA: Incorporate the geometry shader:
The curvature comb is implemented by creating a new Geometry shader program. The results for this for Pentagon and basis shape are given below:
![abc](https://github.com/Rohit8y/subDivisionSplines/blob/main/gS_pent_Comb.png?raw=true)

![abc](https://github.com/Rohit8y/subDivisionSplines/blob/main/gS_basis_comb.png?raw=true)


## AF: Visualise control point influence: 
To implement this additional feature I created a new renderer and while running this make sure that control net is not checked. When one of the control points is clicked, the influence of this point is highlighted with pink color. The results of this are given below:

![abc](https://github.com/Rohit8y/subDivisionSplines/blob/main/AF_pent.png?raw=true)
![abc](https://github.com/Rohit8y/subDivisionSplines/blob/main/AF_G.png?raw=true)





