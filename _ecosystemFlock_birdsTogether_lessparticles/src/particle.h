#ifndef PARTICLE_H
#define PARTICLE_H

#include "ofMain.h"

class flockingForce {
public:
	
	int			count;
	ofVec2f	sum;
	float		distance;
	float		strength;
	
};


class particle
{
    public:
        ofVec2f pos;
        ofVec2f vel;
        ofVec2f frc;   // frc is also know as acceleration (newton says "f=ma")
		
        ofVec2f prevPos;
    
        ofVec2f origPos;
		unsigned int bitFlagW;
		unsigned int bitFlagH;
	
        particle();
		virtual ~particle(){};
    
        void resetToOriginalPosition();

        void resetForce();
		void addForce(float x, float y);
		void addRepulsionForce(float x, float y, float radius, float scale);
		void addAttractionForce(float x, float y, float radius, float scale);
    
		void addRepulsionForce(particle &p, float radius, float scale);
		void addAttractionForce(particle &p, float radius, float scale);
        void addClockwiseForce(particle &p, float radius, float scale);
        void addCounterClockwiseForce(particle &p, float radius, float scale);
	

		
		void addDampingForce();
    
        void addForFlocking(particle &p);
        void addFlockingForce();
        void rotate();
        flockingForce cohesion;
        flockingForce seperation;
        flockingForce alignment;
        
		void setInitialCondition(float px, float py, float vx, float vy);
        void update();
        void draw();
    
        void drawBird();
        void drawWeed();
        void drawSand();
	
		void bounceOffWalls();
        float damping;
        vector < ofPoint > pts;
    
        float angle;
        ofImage bird;
        ofImage weed;
        ofImage firefly;
    
        float birdSize;
        float r;


    protected:
    private:
};

#endif // PARTICLE_H
