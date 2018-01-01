import Foreign
import Foreign.C.Types
import Foreign.C.String


-- Foreign function imports
foreign export ccall
  gameUpdate :: IO()
  
foreign import ccall safe "winfuncs.h"
  hswinmain :: Int -> Int -> Int
  
foreign import ccall unsafe "winfuncs.h"
  clearScreen :: IO ()
  
foreign import ccall unsafe "winfuncs.h"
  isKeyDown :: CString -> Int


data GameState = GameState {
    gs_round :: Int,
    gs_score :: Int
  } deriving (Show)


-- This function is called from the 
-- C part, outside of the main game loop
gameUpdate :: IO()
gameUpdate = do 
  clearScreen
  mycs <- newCString "up"
  let upPressed = isKeyDown mycs
  let text =  "downPressed: " ++ show upPressed
  print text
  return ()


  
main = do 
  print "Hello from Haskell main"
  let res = hswinmain 800 600
  print res
  return ()
