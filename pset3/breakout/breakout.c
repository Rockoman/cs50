//Marc LaRocco
// breakout.c
//
// Computer Science 50
// Problem Set 3
//

// standard libraries
#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Stanford Portable Library
#include <spl/gevents.h>
#include <spl/gobjects.h>
#include <spl/gwindow.h>

// height and width of game's window in pixels
#define HEIGHT 600
#define WIDTH 400

// number of rows of bricks
#define ROWS 5

// number of columns of bricks
#define COLS 10

// radius of ball in pixels
#define RADIUS 10

// lives
#define LIVES 3

// prototypes
void initBricks(GWindow window);
GOval initBall(GWindow window);
GRect initPaddle(GWindow window);
GLabel initScoreboard(GWindow window);
void updateScoreboard(GWindow window, GLabel label, int points);
GObject detectCollision(GWindow window, GOval ball);

int main(void)
{
    // seed pseudorandom number generator
    srand48(time(NULL));

    // instantiate window
    GWindow window = newGWindow(WIDTH, HEIGHT);

    // instantiate bricks
    initBricks(window);

    // instantiate ball, centered in middle of window
    GOval ball = initBall(window);

    // instantiate paddle, centered at bottom of window
    GRect paddle = initPaddle(window);

    // instantiate scoreboard, centered in middle of window, just above ball
    GLabel label = initScoreboard(window);

    // number of bricks initially
    int bricks = COLS * ROWS;

    // number of lives initially
    int lives = LIVES;

    // number of points initially
    int points = 0;

    //declare velocity of ball
    double xvelocity = drand48() + 2.5;
    double yvelocity = 3.5;
    
    //wait for click to start
    waitForClick();

    // keep playing until game over
    while (lives > 0 && bricks > 0)
    {
    
        //update scoreboard
        updateScoreboard(window, label, points);
        
        //move the ball
        move(ball, xvelocity, yvelocity);
        pause(20);
        
        //instantiate a mouse event
        GEvent event = getNextEvent(MOUSE_EVENT);
        
        //validate the event
        if (event!= NULL)
        {
            if (getEventType(event) == MOUSE_MOVED)
            {
                //paddle moves with mouse on the x axis
                double x = getX(event) - (getWidth(paddle) / 2);
                //set height 
                double y = HEIGHT - 100;
                setLocation(paddle, x, y);
            }
        
        }
        
        //instantiate from detectCollision
        GObject object = detectCollision(window, ball);
        if (object != NULL)
        {
        
            //ball hitting the paddle
            if(object == paddle)
                yvelocity = -yvelocity;
            else if(strcmp(getType(object), "GRect") == 0)
            {
                removeGWindow(window, object);
                yvelocity = -yvelocity;
                points = points + 1;
                bricks = bricks - 1;
            
            }
          
        }
        
        //calculate lives
        if(getY(ball) > 600)
        {
            lives = lives - 1;
            
            //reset ball to starting position
            setLocation(ball, WIDTH / 2 - RADIUS, HEIGHT / 2 + RADIUS); 
            waitForClick();
        
        }
        
        //detech when the ball hits the side and the top walls
        //top wall
        if(getY(ball) <= 0)
            yvelocity = -yvelocity;
        //left wall
        if(getX(ball) <= 0)
            xvelocity = -xvelocity;
        //right wall
        if(getX(ball) + getWidth(ball) >= WIDTH)
            xvelocity = -xvelocity;
     
        //player wins
        if (points == 50)
        {
            GLabel winner = newGLabel ("You've cleared the game!");
            setFont(winner, "SansSerif-40");
            setColor(winner, "GREEN");
            setLocation(winner, 15, 300);
            add(window, winner);
        }   
    }

    // wait for click before exiting
    waitForClick();

    // game over
    closeGWindow(window);
    return 0;
}

/**
 * Initializes window with a grid of bricks.
 */
void initBricks(GWindow window)
{
    //declare variables 
    int xSpace = 7;
    int ySpace = 7;
    int bHeight = 12;
    int bWidth = 33;
    
    
    //create 2d array
    GRect bricks[COLS][ROWS];
    
    //loop 2d array (COLUMNS FIRST!!)
    for(int i = 0; i < COLS; i++)
        for (int j = 0; j < ROWS; j++)
            {
                //create bricks and location
                bricks[i][j] = newGRect( ((i * bWidth) + (i * xSpace) + 1), (j * bHeight) + (j * ySpace) + 1 * bHeight, bWidth, bHeight);
                
                //set brick colors
                if(j == 0)
                    setColor(bricks[i][j], "RED");
                else if (j == 1)
                    setColor(bricks[i][j], "ORANGE");
                else if (j == 2)
                    setColor(bricks[i][j], "YELLOW");
                else if (j == 3)
                    setColor(bricks[i][j], "GREEN");
                else if (j == 4)
                    setColor(bricks[i][j], "CYAN");
              
                //fill in the color!
                setFilled(bricks[i][j], true);
                
                //add bricks!
                add(window, bricks[i][j]);                    
                    
            }

}


/**
 * Instantiates ball in center of window.  Returns ball.
 */
GOval initBall(GWindow window)
{
{
    //create an oval (game ball) and put it in the center of the screen.
    GOval ball = newGOval(WIDTH / 2 - RADIUS, HEIGHT / 2 + RADIUS, RADIUS * 2, RADIUS * 2);
    
    //set the ball color to black and fill it
    setColor(ball, "BLACK");
    setFilled(ball, true);
    
    //add the ball to the playing window
    add(window, ball);
    
    return ball;
}

}

/**
 * Instantiates paddle in bottom-middle of window.
 */
GRect initPaddle(GWindow window)
{
    //create a rect (paddle) and put it near the bottom of the screen
    GRect paddle = newGRect((WIDTH / 2) - (80 / 2), 500, 80, 12);
    
    //set the color and fill it
    setColor(paddle, "BLACK");
    setFilled(paddle, true);
    
    //add the paddle to the playing window
    add(window, paddle);
    
    return paddle;

}

/**
 * Instantiates, configures, and returns label for scoreboard.
 */
GLabel initScoreboard(GWindow window)
{
    //create a label
    GLabel label = newGLabel("1");
    setFont(label, "SansSerif-50");
    setColor(label, "RED");
    add(window, label);
    
    return label;
}

/**
 * Updates scoreboard's label, keeping it centered in window.
 */
void updateScoreboard(GWindow window, GLabel label, int points)
{
    // update label
    char s[12];
    sprintf(s, "%i", points);
    setLabel(label, s);

    // center label in window
    double x = (getWidth(window) - getWidth(label)) / 2;
    double y = (getHeight(window) - getHeight(label)) / 2;
    setLocation(label, x, y);
}

/**
 * Detects whether ball has collided with some object in window
 * by checking the four corners of its bounding box (which are
 * outside the ball's GOval, and so the ball can't collide with
 * itself).  Returns object if so, else NULL.
 */
GObject detectCollision(GWindow window, GOval ball)
{
    // ball's location
    double x = getX(ball);
    double y = getY(ball);

    // for checking for collisions
    GObject object;

    // check for collision at ball's top-left corner
    object = getGObjectAt(window, x, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's top-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-left corner
    object = getGObjectAt(window, x, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // check for collision at ball's bottom-right corner
    object = getGObjectAt(window, x + 2 * RADIUS, y + 2 * RADIUS);
    if (object != NULL)
    {
        return object;
    }

    // no collision
    return NULL;
}
