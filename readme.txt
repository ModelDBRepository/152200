The model is associated with the following papers:

Gingrich KJ, Byrne JH (1985) Simulation of synaptic depression,
posttetanic potentiation, and presynaptic facilitation of synaptic
potentials from sensory neurons mediating gill-withdrawal reflex in
Aplysia. J Neurophysiol 53:652-669.

Zhou L, Baxter DA, Byrne JH (2014) Contribution of PKC to the
Maintenance of 5-HT Induced Short-Term Facilitation at Sensorimotor
Synapses of Aplysia. J Neurophysiol

Model was constructed under Visual Studio 2010 c++.  Free Visual
Studio can be downloaded at
http://www.visualstudio.com/en-us/products/visual-studio-express-vs.aspx.

To run the simulations associated with Zhou et al (2014).

1) Download and install Visual Studio from the above website (visual
studio 2013 express version).
2) On the File menu, point to New, and then click Project….
3) In the Project Types area, click Visual c++, and then click Empty
Project. Type G-B model as the project name and then click OK.
4) Download and unzip ZhouEtAl2014.zip from ModelDB. Locate
G-B_lian.cpp.  For easy access, move G-B_lian.cpp into the folder G-B
model.
5) Right-click the Source Files folder in Solution Explorer and point
to Add. Then click Existing Item….
6) In the adding Existing Item Wizard, choose the link of G-B_lian.cpp
(directory and locations). Click Add.
7) Compile and run G-B_lian.cpp (Click Build Solution, and then click
Start Without Debugging).
8) Running G-B_lian.cpp produces output file release.txt and
supply_rate.txt .
a) release.txt : synaptic release and normalized synaptic release
b) supply_rate.txt : calcium regulation and vesicle mobilization and
dynamics of PKC activation.
 Release.txt is used to produce the plots of solutions shown in
 Figures. 2, 3 , 5,6, 7.  Supply_rate.txt is used to plots of
 solutions shown in Figures.4.
9) All of parameter related to the simulations in Zhou et al.(2014)
are contained in the comments of G-B_lian.cpp.  For a particular
simulation in Zhou et al (2014), you need to modify the parameters in
G-B_lian.cpp according to the comments and do the step 7 and 8 again.
