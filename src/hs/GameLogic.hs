


module GameLogic where

import Foreign
import Foreign.C.Types
import Foreign.C.String



data Movement = Movement {
    xdir :: Int,
    ydir :: Int,
    velocity:: Int
    
  } deriving (Show)
  
  
data PlayerInput = InputUP | InputDOWN | InputLEFT | InputRIGHT deriving (Show)
  
processMovement :: Maybe PlayerInput -> Movement -> Movement
processMovement Nothing m = m
processMovement (Just InputUP) (Movement x y v) = (Movement x (y+1) v)
processMovement (Just InputDOWN) (Movement x y v) = (Movement x (y-1) v)
processMovement (Just InputLEFT) (Movement x y v) = (Movement (x-1) y v)
processMovement (Just InputRIGHT) (Movement x y v) = (Movement (x-1) y v)


-- Local fake stub
isKeyDown' :: String -> (Maybe PlayerInput)
isKeyDown' "up" = (Just InputUP)
isKeyDown' "down" = Nothing
isKeyDown' "left" = (Just InputLEFT)

x -: f = f x

processInputs :: Movement
processInputs = (Movement 0 0 1) -: processMovement (isKeyDown' "up") -: processMovement (isKeyDown' "down") -: processMovement (isKeyDown' "left")
