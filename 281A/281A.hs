import Control.Monad
import Data.Char

main :: IO ()
main = interact f
f (c:cs) = toUpper c:cs
f cs = cs
