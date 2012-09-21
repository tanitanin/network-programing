
module Server where

import Data.ByteString (ByteString)
import qualified Data.ByteString as B
import Data.Map (Map)
import qualified Data.Map as M
import Data.Text (Text)
import qualified Data.Text as T

import qualified Network.MessagePackRpc.Client as MP

import Types

newtype HogeT m a
  = HogeT { unHogeT :: StateT () m a }
  deriving (Monad, MonadIO, MonadTrans, MonadState ())

get :: Text -> HogeT (Text)
get = MP.method "get"

set :: Text -> Text -> HogeT (Text)
set = MP.method "set"


