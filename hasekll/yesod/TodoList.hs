{-# LANGUAGE TypeFamilies, QuasiQuotes, TemplateHaskell #-}
{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FlexibleContexts, EmptyDataDecls, GADTs #-}
{-# LANGUAGE OverloadedStrings #-}
module Main where

import Yesod
import Database.Persist.Sqlite
import Data.Text
data TodoList = TodoList ConnectionPool

share [mkPersist sqlSettings, mkMigrate "migrateAll"] [persist|
Todo
  title Text
  stauts Text
|]

instance YesodPersist TodoList where
    type YesodPersistBackend TodoList = SqlPersist

    runDB action = do
        TodoList pool <-getYesod
        runSqlPool action pool

mkYesod "TodoList" [parseRoutes|
/todos IndexR GET POST
/todos/#Int TodoItemR GET PUT DELETE
/todos/#Int/add AddR GET
/todos/#Int/edit EditR GET
|]
instance Yesod TodoList

getIndexR :: Handler RepHtml
getIndexR = do
    todos <- runDB $ selectList [TodoTitle !=. ""][]
    defaultLayout [whamlet|
$if Prelude.null todos
    <p>Realx ~ Nothing to do now
$else
  <ul>
    $forall todo <- todos
      <li>todo
|]


postIndexR :: Handler RepHtml
postIndexR = undefined

getTodoItemR :: Int -> Handler RepHtml
getTodoItemR = undefined

putTodoItemR :: Int -> Handler RepHtml
putTodoItemR = undefined

deleteTodoItemR :: Int -> Handler RepHtml
deleteTodoItemR = undefined

getAddR :: Int -> Handler RepHtml
getAddR = undefined

getEditR :: Int -> Handler RepHtml
getEditR = undefined

main :: IO ()
main = do
    withSqlitePool "test.db" 5 $ \pool -> do
        runSqlPool (runMigration migrateAll) pool
        runSqlPool (insert $ Todo "A" "B") pool
        warpDebug 3000 (TodoList pool)
