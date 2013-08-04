import Data.List (intercalate)

string2int str = (read str :: Int)
get_nxn x = [1..x^2]

solve n [] = []
solve n a = do
    (take n a) ++ (take n $ reverse a) ++ (solve n $ (reverse $ drop n $ reverse $ drop n a))

main :: IO ()
main = do
    str <- getLine
    putStrLn $ intercalate " " (map show $ solve (floor ((fromIntegral (string2int str)) / (fromIntegral (2 :: Int)))) $ (get_nxn $ string2int str))

