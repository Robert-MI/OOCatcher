This project is a simulation of a figure body capable of operating in two modes: Snowball mode and Walker mode.
In Snowball mode, the body rotates its arm to aim at a target and throws a snowball when all previously touching segments detach from the object.
The system logs the snowball's initial position, velocity, and whether the target was hit.

In Walker mode, the body uses a step function to move toward a circular object.
After each step, the arm automatically rotates toward the object. When at least three free ending segment points (fingers) touch the object’s
perimeter or interior, the body is considered to have successfully grabbed it. After every move, it is also verified that at least two points of the
body remain in contact with the ground.

The body consists of multiple segments: two legs, torso, two arms, and three fingers extending from the right hand.
All segments rotate around their starting points and stay connected throughout the simulation. Ground level is set at y = -7.07107,
and basic anthropomorphic limitations are enforced by clamping segment rotation angles to the range [-π, π].

Target and object positions are imputed from terminal. The program is built using CMake. Two executables are produced: WalkerMode and SnowballMode.