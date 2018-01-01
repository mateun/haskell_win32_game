
data GameState = GameState {
	gs_round :: Int,
	gs_score :: Int
	} deriving (Show)


-- This function is called from the 
-- C part, outside of the main game loop
gameUpdate :: IO()
gameUpdate = do 
				print "in haskell game update\n"
				clearScreen
				

foreign export ccall
	gameUpdate :: IO()
	
foreign import ccall safe "winfuncs.h"
	hswinmain :: Int -> Int -> Int
	
foreign import ccall safe "winfuncs.h"
	clearScreen :: IO ()
	
main = do 
		print "Hello from Haskell main"
		let res = hswinmain 800 600
		print res
		return ()
