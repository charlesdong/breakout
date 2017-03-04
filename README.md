# Breakout

Breakout is a classic 2D game released in 1976 on the Atari 2600 console. And this is a Breakout clone.

## Latest progress

Now able to play sounds. In the game, 4 sounds are played. One is the main sound of Breakout which is looped during the whole time. Others are only played when specific events take place (e.g. the ball bounces the paddle, a brick is destroyed).

## Game rules

In the game, you have a ball and a paddle, and there are some bricks on the top of the screen. The ball will rebounce if it collides with a brick, the edge or the paddle. Also if the ball collides with a brick, the brick will be destroyed (if it's non-solid).

Your target is to destroy all non-solid (breakable) bricks. Once they are all destroyed, you win.

You also have a certain number of lives (usually 3). Every time you failed to catch the ball, you lose a life. Once all the lives are lost, you lose, and restarting the game is required if you want to continue to play.

### Controls

AD to move the paddle in the horizontal direction.

Space to launch the ball.

Escape to quit.

## Download

Sorry, binaries for this game is currently unavailable.

## More about the game

Actually you can find the implement details on the website https://learnopengl.com/ (in the menu directory In Practice/2D Game). But when I know more and more about game developing, I found that the code on the website is a bit awful. To write better code (this can also speed up the game), I started this project.
