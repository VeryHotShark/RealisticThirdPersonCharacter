# RealisticThirdPersonCharacter on Unreal Engine 5

In this Project I tried to create most realistically playable character
using FemaleAnimsetPro + Mixamo Animations.

**Player is Able to:**

- Walk
- Run
- Jump
- Crouch
- Take cover behind obstacles

**Controls:**

- WASD -> Movement
- Spacebar -> Jump
- Ctrl -> Crouch
- Shift -> Run
- E -> Enter/Exit Cover

The character is controlled by the player and moves using "Strafe Locomotion." It can perform all the actions mentioned above, along with additional features I will describe below.

For most animations, I used "root-motion," except for jumping, which is physics-based, and moving during cover, which is based on generated animation curves.

I used most of the animations from the package, but for some, I needed to download animations from Mixamo (mainly for cover). To achieve the most realistic effect, I implemented the following additions to the character:

**Start/Stop Transitions:**

![StartStop](https://github.com/VeryHotShark/RealisticThirdPersonCharacter/assets/31168287/b2cc4795-e35a-4e49-a863-3f7a167edeb7)

There are start and stop animations for walking, running, and crouching. For Start and Loop animations, I added "Sync Markers" for the character's steps. I also tried adding them to Stop animations, but they didn't give me the desired effect, so I used a standard blend.

I also removed diagonal starts because the standard blends between 4-directional animations reduced realism.

**Additive Jump/InAir/Land:**

![JumpsDirectional](https://github.com/VeryHotShark/RealisticThirdPersonCharacter/blob/main/JumpsDirectional.gif)
![Landing](https://github.com/VeryHotShark/RealisticThirdPersonCharacter/blob/main/Landing.gif)

Due to the lack of directional jump animations and the various leg orientations in "strafe locomotion," I used "Blend Additive" nodes to blend the jump/loops in the air/landing with the character's current movement direction. It doesn't look perfect, but it appeared more natural than without additives.

**Physical Animation:**

![PhysicalAnimation](https://github.com/VeryHotShark/RealisticThirdPersonCharacter/assets/31168287/d84aa4a7-f306-404e-8500-0c34968e82c0)


I added the "Physical Animation" component to prevent body parts from clipping through walls (to some extent). All bones below the "pelvis" are set to simulate physics/ragdoll with high settings to follow the current animation.

**Leg IK / Control Rig:**

![LegIK1](https://github.com/VeryHotShark/RealisticThirdPersonCharacter/assets/31168287/bcfd6da6-a5a8-4878-a270-fa867e608066)
![LegIK2](https://github.com/VeryHotShark/RealisticThirdPersonCharacter/assets/31168287/80986138-28f5-4ec9-ba57-3206ed8b7349)

Using the "Control Rig," I created leg inverse kinematics (IK) to correctly snap the character's feet to the ground (prevent floating). Only the location is snapped, not the orientation. It was my first experience with Control Rigs, and I see it as a powerful tool with many possibilities that I have only just scratched the surface of.

**Aim Offset / Local Space To Component:**

![AimOffset](https://github.com/VeryHotShark/RealisticThirdPersonCharacter/assets/31168287/9585b8f9-18ef-4d0c-872b-74fa3498e219)


The character's head and torso follow the direction of the camera (with limitations). The head is controlled using "Aim Offset," and the torso is controlled using "Local Space To Component" in the character's Animation Blueprint. I also created an alternative version using Control Rigs, but I couldn't parameterize it to my satisfaction, so I left it as a comment in the AnimGraph.

Ideally, Control Rigs would be better for replacing Local Space To Component. However, my limited knowledge of Control Rigs prevented me from doing so.

**Turn in Place:**

![TurnInPlace](https://github.com/VeryHotShark/RealisticThirdPersonCharacter/blob/main/TurnInPlace.gif)

The character can turn towards the camera during idle when the difference between the camera's direction and the character exceeds 60 degrees. The camera must remain stationary for 0.5 seconds. The character turns whether standing or crouching.

The turn is achieved using curves generated in the animation. I created a simple Blueprint Animation Modifier that extracts the rotation from the animation and maps it to a range of 0-1. This range is then used to interpolate the character by "X" degrees with minimal foot sliding. It is most noticeable when the character turns while crouching because animations were well-prepared for that.

For turns while standing, I had to download animations from Mixamo and retarget them to the character, which unfortunately stands out from the rest and includes errors/sliding (also due to the imperfections of my retargeter). However, I decided to keep it to demonstrate that the system works with properly prepared animations (crouching). However, you can disable it and see the result without turning in place by toggling the TurnInPlace boolean in ABP_Katiuszy.

**Cover System:**

![CoverSystem](https://github.com/VeryHotShark/RealisticThirdPersonCharacter/blob/main/CoverSystem.gif)

The cover system consists of two components:

"CharacterCoverComponent," which handles finding cover, managing it, and passing input to it.
"CoverActor," which has a path and interprets the input passed to it (moves the player).
Both components are implemented in C++ and have their Blueprint versions. The player's path is created using splines, and covers are manually placed in the scene (the red boxes on the scene).

The character can:

Enter and exit cover
Move along the spline
Dynamically adjust posture to cover height
Lean out of cover at the ends
The movement input is relative to the camera and the cover path, similar to "Gears of War." If the input is perpendicular to the obstacle, the character exits cover (however, I didn't implement camera lock for curved paths, so you have to manually rotate the camera to avoid accidentally leaving cover).

The character is moved along the spline using speeds extracted from the animations (I created another Animation Modifier for this). I chose curves instead of root motion for full control and precision over the character's movement. However, the animations are from Mixamo, so they are not perfect, as with Turn in Place.

**Cloth Simulation:**

![CoverSystem](https://github.com/VeryHotShark/RealisticThirdPersonCharacter/blob/main/ClothSimulation.gif)

I also added cloth simulation to the skirt for decorative purposes. It behaves strangely in some places but helps blend animations.

**Post-Mortem:**

In conclusion, I see that there are still many things that could be refined or fixed, and there are occasional popping transitions, especially when rapidly changing input directions. However, I am quite satisfied with the result and would gladly listen to feedback :)
