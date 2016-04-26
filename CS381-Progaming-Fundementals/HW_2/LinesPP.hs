module SVG where

import System.IO

--import Semantics

ppLines :: Lines -> IO ()
ppLines ls = withFile "lines.svg" WriteMode $ flip hPutStrLn $ toSVG ls

toSVG :: Lines -> String
toSVG ls =
  "<svg width='400' height='400' xmlns='http://www.w3.org/2000/svg'>\n" ++
  "<g transform='translate(0,400)'>\n<g transform='scale(1,-1)'>\n" ++
  concatMap lineSVG ls ++ "</g>\n</g>\n</svg>"

lineSVG :: Line -> String
lineSVG (x1,y1,x2,y2) =
  "<line stroke='black' stroke-width='2'" ++
  "  x1='" ++ show x1 ++
  "' y1='" ++ show y1 ++
  "' x2='" ++ show x2 ++
  "' y2='" ++ show y2 ++ "'/>\n"
