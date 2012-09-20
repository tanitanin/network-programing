import Data.Map
import Network.MessagePackRpc.Server

--set :: Map k a -> k -> a -> IO b
set m key val = return True --Data.Map.insert key val $ m

--get :: Map k a -> k -> IO a
get m key = return Data.Map.lookup key $ m

main :: IO ()
main = let m = Data.Map.empty in
  serve 40320 [("set", toMethod set m), ("get", toMethod get m)]
