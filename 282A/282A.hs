import Control.Monad

main :: IO ()
main = do
        n <- fmap read getLine
        s <- replicateM n getLine
        let plus    = length $ ( filter $ elem '+' ) $ s 
            minus   = length s - plus
        print $ plus - minus
