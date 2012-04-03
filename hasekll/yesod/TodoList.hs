{-# LANGUAGE TypeFamilies, QuasiQuotes, TemplateHaskell #-}
{-# LANGUAGE MultiParamTypeClasses #-}
{-# LANGUAGE FlexibleContexts, EmptyDataDecls, GADTs #-}
{-# LANGUAGE OverloadedStrings #-}
module Main where

import Yesod
import Database.Persist.Sqlite
import Database.Persist.Store
import Data.Text
import GHC.Int
import Control.Applicative
import Text.Blaze.Html5
data TodoList = TodoList ConnectionPool

share [mkPersist sqlSettings, mkMigrate "migrateAll"] [persist|
Todo
  title Text
  status Text
|]

instance YesodPersist TodoList where
    type YesodPersistBackend TodoList = SqlPersist

    runDB action = do
        TodoList pool <-getYesod
        runSqlPool action pool

mkYesod "TodoList" [parseRoutes|
/todos IndexR GET POST
/todos/#Int64 TodoItemR GET PUT
/todos/#Int64/del DelR POST GET
/todos/#Int/add AddR GET
/todos/#Int/edit EditR GET
|]
instance Yesod TodoList

instance RenderMessage TodoList FormMessage where
    renderMessage _ _ = defaultFormMessage

getIndexR :: Handler RepHtml
getIndexR = do
    todos <- runDB $ selectList [TodoTitle !=. ""][]
    defaultLayout [whamlet|
<form method=post action=@{IndexR}>
  Title<input type=text name=title>
  Status<input type=text name=status>
  <input type=submit>
$if Prelude.null todos
    <p>Realx ~ Nothing to do now
$else
  <ul>
    $forall todo <- todos
      <li>#{keyToId $ entityKey todo} : #{todoTitle $ entityVal todo}, #{todoStatus $ entityVal todo}
|]

postIndexR :: Handler RepHtml
postIndexR = do
    (title, status) <- runInputPost $
        (,) <$> ireq textField "title"
            <*> ireq textField "status"
    key <- runDB $ insert $ Todo title status
    redirect (TodoItemR (keyToId $ key))

getTodoItemR :: Int64 -> Handler RepHtml
getTodoItemR tid = do
    todo <- runDB $ get404 (idToKey tid)
    defaultLayout [whamlet|
<p>#{todoTitle todo} ->  #{todoStatus todo}
<a href=@{IndexR}>HomePage
|]

putTodoItemR :: Int64 -> Handler RepHtml
putTodoItemR = undefined

deleteTodoItemR :: Int64 -> Handler RepHtml
deleteTodoItemR tid = do
    runDB $ delete (idToKey tid)
    redirect IndexR

postDelR :: Int64 -> Handler RepHtml
postDelR tid = do
    runDB $ delete (idToKey tid)
    redirect IndexR

getDelR = postDelR

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

idToKey :: GHC.Int.Int64 -> Key backend Todo
idToKey key = Key $ PersistInt64 key

keyToId (Key (PersistInt64 key)) = key

instance ToHtml Int64 where
    toHtml = text . pack . show
