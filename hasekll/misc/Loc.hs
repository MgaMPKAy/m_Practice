module Loc where

import System.FilePath
import Control.Monad
import System.Directory
import Graphics.Rendering.Chart

countLines :: String -> Int
countLines = length . lines

getAllFiles :: FilePath -> IO [FilePath]
getAllFiles path = do
    files <- getDirectoryContents path
    let properFiles = filter (`notElem` [".", ".."]) files
    sub <- forM properFiles $ \f -> do
        let sub = path </> f
        isDir <-doesDirectoryExist sub
        if isDir
            then do
                subfiles <- getAllFiles sub
                return $ sub:subfiles
            else return [sub]
    return (concat sub)

getAllLines files = do
    forM files $ \file -> do
                        content <- readFile file
                        return (takeExtension file, countLines content)
        