## Constellate-Engine
This project represents my attempt at the architecture and implementation of a graphics engine. Creating a 3D application that efficiently utilizes the hardware resources of a machine is a considerable challenge, which varies depending on the available hardware and the exact needs of the application.
To relieve developers of such applications from the significant effort of creating and maintaining software that interacts with a wide range of operating systems and hardware configurations, the concept of a graphics engine emerged. The paper that accompanied this project  exemplifies the issues that a modern graphics engine attempts to solve and possible solutions from both architectural and software implementation perspectives.
The main topics I tried to aproach in writing this project are software implementation concepts in C++, 3D graphics rendering, simulation of physical phenomena, and software architecture concepts. 

A demo video of the engine:


<p align="center">
<img width="800" src="https://s12.gifyu.com/images/Scb6f.gif">
</p>

## Arhitecture
The aritecture of Constellate Engine is based on a basic game loop, systems and the entity-component hierachy. In each iteration of a game loop, systems work on the entities in a scene then a new frame is created. 

<p align="center">
<img width="800" src="https://i.imgur.com/W9Q3s4u.png">
</p>

Each element in the world is actually a container class called Entity. We can store them uniformly and access their internal logic. The developer defines them, and the graphics engine sets them in motion and displays them. This design pattern is known as the Entity-Component model.
However, at an internal level, such an entity doesn't have its own logic. Its behavior is defined by the components it internally holds. As a result, two entities that store different components will exhibit different behaviors. Each Entity will still have an update() function, but it will only run the update() function for each of the components included within it. The 3D application developer will have the possibility to define their own components and decide which components are assigned to an entity. The logic and state of objects are decoupled from the objects themselves. Components contain logic and can collaborate to achieve a specific behavior.


<p align="center">
<img width="800" src="https://i.imgur.com/WwMpdcs.png">
</p>

## Games
The project contains a few demo applications using Constellate Engine. One of them is this game where you have to hit a target with a ball:

<p align="center">
<img width="800" src="https://i.imgur.com/xq0N7yM.png">
</p>



