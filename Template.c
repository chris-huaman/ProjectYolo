/*
* This is the main file that will be commited
*/

//variables
float myZRState[12], myPos[3], otherPos[3], nullList[3],positionOther[12], positionOurs[12], myVel[3], otherVel[3];
int timeElapsed;
int sphereColor; //1 for blue -1 for red

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*Basic utility functions
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/


/**
*This function calculates the absolute value of a given number
*@param number This is the number to be absolute-valued
*@return The distance from zero that the parameter is
*@author davidLi
*/
float aV(float number){
        if(number < 0)        {
                number = -number;
        }
        return number;
} 

/**
*This function determines what color you are by setting the iAmRed variable
*@author chrisHuaman
*/

/**
* @deprecated setSphere is replacement
*/

// void whatColor(){        
// 
// api.getMyZRState( myZRState );
// if(timeElapsed == 0){
//         //If x is > 0 then you are blue, set iAmRed to false
//         if(myZRState[0]/*x coord*/ > 0 ){iAmRed = false;}//ur blue
//         else{iAmRed = true;}
// }        
// 



/**
* This function sets the sphereColor variable
* @param myState current position of robot
* @author jim
*/

int setSphere(ZRState myState){
        //if is red
        if (myState[0] < 0) {
                return -1; //red
        } else {
                return 1; //blue
        }
}

/**
* This function determines whether or not you are in peril of being kicked out of bounds
* @return True if you are in peril, false if you are not
* @author davidLi
* The function has been redone and is needlessly excessive, im going to shorten it down
* but id rather give you something working now since we are too close to deadline
* Detects if you are too close to the edges of the map before 90 secs and returns true if you are
* @param our satellite's x,y,z, then compared to the wall's and checked for distance
* @author chrisHuaman
*/

bool outOfBoundsChecker(float xCoord, float yCoord, float zCoord){
        
		boolean inPeril = false;
		
		wallOneX = -.64;
		wallTwoX = .64;
		wallThreeY = -.80;
		wallFourY = .80;
		wallFiveZ = -.64;
		wallSixZ = .64;	
		
		
		//these are just to switch the values we are working with to positive so that we are
		//always working the right side of the map in pos nums 
		if(xCoord < 0){
			xCoord = xCoord * -1;
			wallOneX = wallOneX * -1;
			wallTwoX = wallTwoX * -1;
			//they both turn negative so that we dont confuse one wall with the other, not really necessary though
		}
		if(yCoord < 0){
			yCoord =yCoord * -1;
			wallThreeY = wallThreeY * -1;
			wallFourY = wallFourY * -1;	
		}
		if(zCoord < 0){
			zCoord = zCoord * -1;
			wallFiveZ = wallFiveZ * -1;
			wallSixZ = wallSixZ * -1;	
		}
		
		
		distanceFromWallOneX = calculateDistanceFrom(xCoord, wallOneX);
		distanceFromWallTwoX = calculateDistanceFrom(xCoord, wallTwoX);
		distanceFromWallThreeY = calculateDistanceFrom(xCoord, wallThreeY);
		distanceFromWallFourY = calculateDistanceFrom(xCoord, wallFourY);
		distanceFromWallFiveZ = calculateDistanceFrom(xCoord, wallFiveZ);
		distanceFromWallSixZ = calculateDistanceFrom(xCoord, wallSizZ);
		
		//if the distance between you and any one of the barriers is .2 or lower return true
        if(distanceFromWallOneX < .3 ||distanceFromWallTwoX < .3 || distanceFromWallThreeY < .3 || distanceFromWallFourY < .3 || distanceFromWallFiveZ < .3 || distanceFromWallSixZ < .3){
		inPeril = true;
		DEBUG(("WE NEED TO GET OUTA HEEEERRR~"));
		}
		else{
		inPeril = false;
        }
	return inPeril;
}


/*
* This function takes you out of bounds when pushed
* @author davidLi
* this function still has yet to be fully redone by me @chris
*/

void gOOOOB(boolean inPeril) //get out of out of bounds
{
        float targetvelocity[3];
                for(int i=0; i < 3; ++i){
                        targetvelocity[i] = -2*myPos[i];
                }
                api.setPositionTarget(nullList);
                api.setVelocityTarget(targetvelocity);
}

/**
* Collects essential information 
* @author davidlLi
*/

void getInfo(){

 api.getOtherZRState(positionOther);
 api.getMyZRState(positionOurs);
 myPos[0] = positionOurs[0]; myPos[1] = positionOurs[1]; myPos[2] = positionOurs[2];
 myVel[0] = positionOurs[3]; myVel[1] = positionOurs[4]; myVel[2] = positionOurs[5];
 otherPos[0] = positionOther[0]; otherPos[1] = positionOther[1]; otherPos[2] = positionOther[2];
 otherVel[0] = positionOther[3]; otherVel[1] = positionOther[4]; otherVel[2] = positionOther[5];

}

/**
* shorthand way to setPositionTarget()
* @param xC x coordinate to travel to 
* @param yC y coordinate to travel to 
* @param zC z coordinate to travel to 
* @author davidLi
*/


/**
* Calculates distance from two specifc POINTS (your x and another x)
* @param coord for object and coord for yourself
* @param is a x , y  or z coord compared to another coord of x, y, or z
* @author chrisHuaman
*/
float calculateDistanceFrom(float point1, float point2){
	float distance = sqrtf((point1 - point2) * (point1 - point2));
	return distance;
}

void QG(float xC, float yC, float zC){

        float loc[3], distance;
        loc[0] = xC;
        loc[1] = yC;
        loc[2] = zC;
        distance = sqrtf((loc[0] - myPos[0])*(loc[0] - myPos[0])+(loc[1] - myPos[1])*(loc[1] - myPos[1])+(loc[2] - myPos[2])*(loc[2] - myPos[2]));

        if(distance > 0.02){
                api.setPositionTarget(loc);
        }else{
                DEBUG(("You are hitting f*ing wood! \n"));
        }
}
                

/**
*This function is called once at the beginning of the simulation
* @author
*/

/**
* Sets the values of a given array 
* @param Float to shove values into
* @param Value to shove into index[0]
* @param Value to shove into index[1]
* @param Value to shove into index[2]
* @author jim
*/
void setValues (float array[3], float a, float b, float c){
        array[0] = a;
        array[1] = b;
        array[2] = c;

}

/**
* Determines if a point is close to another point
*
* @param target[3] first point for comparison
* @param object[3] second point for comparison
* @param distance between the objects to be considered "close"
* @return true if the two objects are within a certain distance false otherwise
* @author jim
*/

bool isClose(float target[3], float object[3], float distance) {
        
        float xDist = object[0] - target[0],
                yDist = object[1] - target[1],
                zDist = object[2] - target[2];
        if(aV(xDist*xDist        + yDist*yDist + zDist*zDist) <= (distance*distance)){
                
                return true;
        }
        
        return false;
}

/**
* Determines if a value on an axis is close to another
*
* @param target first point for comparison
* @param object second point for comparison
* @param distance between the objects to be considered "close"
* @return true if the two values are within a certain distance false otherwise
* @author jim
*/


bool isClose(float target, float object, float distance) {
        
        if (aV(target - object) < distance){
                return true;
        } else {
                return false;
        }
        
}

void init(){

        timeElapsed = 0;
        nullList[0] = 0;
        nullList[1] = 0;
        nullList[2] = 0;

}

/**
* This function is called once per second
* Most implementation of functions will go here
*/
void loop(){

        getInfo();
        setSphere(myZRState);
        /*Code vvvv  */
        
        
    QG(0,0,0);
    
    /*Syntacies ~ and ~ functions:
    DON'T TOUCH ANYTHING IN VOID LOOP THAT IS OUTSIDE CODE!
    Your position is myPos[3] Other position is otherPos[3]. 
        Your velocity is myVel[3] Other velocity is otherVel[3]
        iAmRed tells you if you are red.True if red, else false
        QG(float x, float y, float z) is a convenient function
    that goes to a location without needing to store a list
    aV() is absolute value function; timeElapsed is time elapsed
    No need to avoid out of bounds; already have gOOOOB()
        */
        
        
        
        
        /*Code ^^^^  */
        gOOOOB(outOfBoundsChecker(myPos[0], myPos[1], myPos[2]));//GOOB ACTIVATE!
        timeElapsed++;
}