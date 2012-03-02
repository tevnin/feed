#include "particle.h"
#include "ofMain.h"


//------------------------------------------------------------
particle::particle(){
	setInitialCondition(0,0,0,0);
	damping = 0.01f;
    
    seperation.distance		= 20;
	alignment.distance		= 80;
	cohesion.distance		= 40;
	
	seperation.strength		= .07;
    alignment.strength		= .015;
	cohesion.strength		= .015;
    
    //bird.loadImage("bird.png");
    //weed.loadImage("tumbleweed3.png");
    //firefly.loadImage("firefly.png");
    //birdSize = 10;
    r = 1.75;
}

//------------------------------------------------------------
void particle::resetForce(){
    // we reset the forces every frame
    frc.set(0,0);
    
    // reset the flock info: 
	cohesion.count 	    = 0;
	seperation.count	= 0;
	alignment.count		= 0;
	
	cohesion.sum.set(0,0); 	
	seperation.sum.set(0,0); 	
	alignment.sum.set(0,0); 	
}

//------------------------------------------------------------
void particle::addForce(float x, float y){
    // add in a force in X and Y for this frame.
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

//------------------------------------------------------------
void particle::addRepulsionForce(particle &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
		p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
    }
}

//------------------------------------------------------------
void particle::addAttractionForce(particle & p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
		p.frc.x = p.frc.x + diff.x * scale * pct;
        p.frc.y = p.frc.y + diff.y * scale * pct;
    }
	
}

//------------------------------------------------------------
void particle::addClockwiseForce(particle &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x - diff.y * scale * pct;
        frc.y = frc.y + diff.x * scale * pct;
		p.frc.x = p.frc.x + diff.y * scale * pct;
        p.frc.y = p.frc.y - diff.x * scale * pct;
    }
}

//------------------------------------------------------------
void particle::addCounterClockwiseForce(particle &p, float radius, float scale){
	
	// ----------- (1) make a vector of where this particle p is: 
	ofVec2f posOfForce;
	posOfForce.set(p.pos.x,p.pos.y);
	
	// ----------- (2) calculate the difference & length 
	
	ofVec2f diff	= pos - posOfForce;
	float length	= diff.length();
	
	// ----------- (3) check close enough
	
	bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
	
	// ----------- (4) if so, update force
    
	if (bAmCloseEnough == true){
		float pct = 1 - (length / radius);  // stronger on the inside
		diff.normalize();
		frc.x = frc.x + diff.y * scale * pct;
        frc.y = frc.y - diff.x * scale * pct;
		p.frc.x = p.frc.x - diff.y * scale * pct;
        p.frc.y = p.frc.y + diff.x * scale * pct;
		
    }
}

//------------------------------------------------------------
void particle::addForFlocking(particle &p){
	
	ofVec3f diff, diffNormalized;
	float distance;
	
	diff			= p.pos - pos;
	distance		= diff.length();
	diffNormalized	= diff;
	diffNormalized.normalize();
    
	if( distance > 0 && distance < seperation.distance ){
		seperation.sum += diffNormalized;
		seperation.count++;
	}
	
	if( distance > 0 && distance < alignment.distance ){
		alignment.sum += p.vel.getNormalized();
		alignment.count++;
	}
	
	if( distance > 0 && distance < cohesion.distance ){
		cohesion.sum += p.pos;
		cohesion.count++;
	}
}

//------------------------------------------------------------
void particle::addFlockingForce(){
	
	
	
	// seperation
	if(seperation.count > 0){							// let's add seperation :)
		seperation.sum /= (float)seperation.count;
		float sepFrc 	= seperation.strength;
		frc -= (seperation.sum.normalized()		    * sepFrc);
	}
	
	// alignment
	if(alignment.count > 0){
		alignment.sum /= (float)alignment.count;
		float alignFrc 	= alignment.strength;
		frc += (alignment.sum		* alignFrc);		// don't normalize the allignment, just use the average
	}
	
	// cohesion
	if(cohesion.count > 0){
		cohesion.sum /= (float)cohesion.count;
		cohesion.sum -= pos;
		float cohFrc 	= cohesion.strength;
		frc += (cohesion.sum.normalized()			* cohFrc);
	}
	
}


//------------------------------------------------------------

void particle::resetToOriginalPosition(){
	
	
	pos = origPos;
	vel.set(0,0);
	
}


//------------------------------------------------------------
void particle::addDampingForce(){
	
	// the usual way to write this is  vel *= 0.99
	// basically, subtract some part of the velocity 
	// damping is a force operating in the oposite direction of the 
	// velocity vector
	
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

//------------------------------------------------------------
void particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
	vel.set(vx,vy);
	
	origPos = pos;
	
}

//------------------------------------------------------------
void particle::update(){	
	vel = vel + frc;
	pos = pos + vel;
}

//------------------------------------------------------------
void particle::draw(){
	
    /*
   	ofFill();
    ofCircle(pos.x , pos.y , 5);
	ofCircle(pos.x , pos.y , 2 *vel.x + vel.y);
	ofCircle(pos.x ,pos.y -10 , 0.3 +  (vel.x + vel.y));
	ofCircle(pos.x , pos.y - 2* (vel.x*vel.y) ,  vel.x + vel.y);
    
	
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y, 0);
    ofRotateZ(90);
    bird.draw(pos.x, pos.y, birdSize, birdSize);	
	ofPopMatrix();
     */
}

//------------------------------------------------------------
void particle::drawBird(){
    
    float angle = (float)atan2(-vel.y, vel.x);
    float theta =  -1.0*angle;
	float heading2D = ofRadToDeg(theta)+90;
    r = ofMap(pos.y, 0, ofGetHeight(), 2, 1);
    ofPushMatrix();
    ofTranslate(pos.x, pos.y);
    ofRotateZ(heading2D);
	ofBeginShape();
    ofVertex(0, -r*2); //top
    ofVertex(0.5, -r); //one lower, right side
    ofVertex(r*3, r*2); // far right
    ofVertex(r, r*1.5);// one up from bottom, right side
    ofVertex(0, r*2.5); // bottom
    ofVertex(-r, r*1.5); // one up from bottom, left side
    ofVertex(-r*3, r*2); // far left
    ofVertex(-0.5, -r); // one down from top, left side
    ofEndShape(true);
    ofPopMatrix();
    //pos.y = ofMap(sin(ofGetElapsedTimef()), -1, 1, pos.y-2, pos.y+2);
}

//------------------------------------------------------------
void particle::drawWeed(){
    
    //weed.draw(pos.x, pos.y, 30, 30);
    
}

//------------------------------------------------------------
void particle::drawSand(){
    
    
    float firefly_r = ofMap(sin(ofGetElapsedTimef()), -1, 1, 4, 10);
    
    ofPushMatrix();
    ofTranslate(pos.x, pos.y, 0);
    ofRotateZ(angle * RAD_TO_DEG);
    
    ofCircle(pos.x, pos.y, 2);
    ofSetColor(255, 255, 255);
    ofEnableAlphaBlending();
    //firefly.draw(pos.x-2, pos.y-2, firefly_r, firefly_r);
    
    ofPopMatrix();
    
    float dx = pos.x - prevPos.x;
	float dy = pos.y - prevPos.y;
	
	angle = atan2(dy, dx);
    
	prevPos.x = pos.x;
	prevPos.y = pos.y;
    
    
}

//------------------------------------------------------------
void particle::rotate() {
    
    float dx = pos.x - prevPos.x;
	float dy = pos.y - prevPos.y;
	
	angle = atan2(dy, dx);
    
	prevPos.x = pos.x;
	prevPos.y = pos.y;
    
    
}


//------------------------------------------------------------
void particle::bounceOffWalls(){
	
	// sometimes it makes sense to damped, when we hit
	bool bDampedOnCollision = true;
	bool bDidICollide = false;
	
	// what are the walls
	float minx = 0;
	float miny = 0;
	float maxx = ofGetWidth();
	float maxy = ofGetHeight();
	
	if (pos.x > maxx){
		pos.x = maxx; // move to the edge, (important!)
		vel.x *= -2;
		bDidICollide = true;
	} else if (pos.x < minx){
		pos.x = minx; // move to the edge, (important!)
		vel.x *= -2;
		bDidICollide = true;
	}
	
	if (pos.y > maxy){
		pos.y = maxy; // move to the edge, (important!)
		vel.y *= -2;
		bDidICollide = true;
	} else if (pos.y < miny){
		pos.y = miny; // move to the edge, (important!)
		vel.y *= -2;
		bDidICollide = true;
	}
	
	if (bDidICollide == true && bDampedOnCollision == true){
		vel *= 0.3;
	}
	
}
