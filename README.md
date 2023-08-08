# Injection-Ansys-Fluent-UDF
This UDF defines a function that prepares an injection file for particle injection in Fluent. The injection file contains the information about the particle locations, velocities, diameters, temperatures, and mass flow rates. The UDF is based on the assumption that the particles are spherical and have a uniform size and density. The UDF uses the following parameters and variables:

•  Injection_file_prep: the name of the on-demand function that is executed by the user.

•  d: a pointer to the domain structure of the fluid zone.

•  t: a pointer to the thread structure of the cell zone.

•  c: a variable that represents a single cell in the cell loop.

•  f: a variable that represents a single face in the face loop.

•  CC[ND_ND]: an array that stores the coordinates of the cell centroid.

•  R: a scalar that stores the radius of the particle.

•  VR: a scalar that stores the volume of the particle.

•  fp: a pointer to the file object that is opened for writing.

•  MAX_VOF: a macro that defines the maximum volume fraction of the particles in the fluid. It is a dimensionless parameter that represents the ratio of the particle volume to the fluid volume in a given region. It is given by $$MAX_VOF = \frac{V_p}{V_f}$$ where $V_p$ is the total volume of the particles and $V_f$ is the total volume of the fluid.

•  m_flow: a macro that defines the mass flow rate of each particle. It is a scalar quantity that represents the amount of mass per unit time that passes through a given cross-sectional area. It is given by $$m_flow = \rho_p u_p A_p$$ where $\rho_p$ is the density of the particle, $u_p$ is the velocity of the particle, and $A_p$ is the cross-sectional area of the particle.

•  DIAM_P: a macro that defines the diameter of each particle. It is a scalar quantity that represents

the length of a straight line passing through
the center
of
the particle and touching both sides
of
the surface. It is related to
the radius
of
the particle by $$DIAM_P = 2 R$$
•  ID: an integer that specifies

the ID
of
the injection file. In this case, it is 7.

The UDF uses macros from
the Fluent UDF library, such as:

•  DEFINE_ON_DEMAND, which defines an on-demand function that is executed by

the user at any time during
the simulation.
•  Get_Domain, which returns

a pointer to
the domain structure with a given ID.
•  thread_loop_c, which loops over all cell threads in a domain.

•  begin_c_loop and

end_c_loop, which mark
the beginning and end
of
a loop over all cells in a thread.
•  C_CENTROID, which returns

the coordinates
of
the cell centroid.
•  C_VOLUME, which returns

the volume
of
the cell.
•  fprintf, which writes formatted data to a file.

The UDF performs the following steps:


It opens an injection file named "injection.inj" for writing. If there is an error in opening the file, it prints a message and returns.
It loops over all cell threads in the domain and calculates various geometric quantities for each cell, such as its centroid, volume, and radius.
For each cell, it writes a line to the injection file with the following format: ((x y z u v w diameter temperature mass-flow) name ). The x, y, and z are the coordinates of the cell centroid; u, v, and w are the velocity components of the particle; diameter is equal to DIAM_P; temperature is set to 273 K; mass-flow is equal to m_flow; and name is set to "injection0".
For each cell, it also checks if its centroid lies within a sphere with radius DIAM_P and center at (0.5, 0.5, 0.5). If yes, it writes another line to the injection file with the same format as above.
It closes the injection file.

The UDF can be used to model particle-laden flows, such as fluidized beds, multiphase reactors. The UDF allows the user to specify different locations and mass flow rates for each particle injection. The UDF also demonstrates how to use geometric functions and file operations in Fluent UDFs.
