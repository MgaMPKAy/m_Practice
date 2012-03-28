{-# LANGUAGE TemplateHaskell, QuasiQuotes #-}
{-# LANGUAGE TypeFamilies, GADTs, MultiParamTypeClasses #-}
{-# LANGUAGE OverloadedStrings, FlexibleContexts #-}
{-# LANGUAGE EmptyDataDecls #-}
{-# LANGUAGE RankNTypes #-}

import Yesod
import Database.Persist
import Database.Persist.TH
import Database.Persist.Sqlite
import Database.Persist.Store
import Data.Text
import Control.Monad.IO.Class (liftIO)
import Control.Monad.Trans.Control
import GHC.Int
import Prelude hiding (catch)

share [mkPersist sqlSettings, mkMigrate "migrateAll"] [persist|
Student
  name Text
Teacher
  name Text
Lesson
  name Text
  totalAvalible Int
  selected Int
StudentLesson
  sid StudentId
  lid LessonId
  UniqueST sid lid
  UniqueSId sid
|]

data LessonChoosing = LessonChoosing ConnectionPool

instance YesodPersist LessonChoosing where
    type YesodPersistBackend LessonChoosing = SqlPersist

    runDB action = do
        LessonChoosing pool <- getYesod
        runSqlPool action pool

mkYesod "LessonChoosing" [parseRoutes|
/ RootR GET
/new/teacher NewTeacheR GET POST
/new/student NewStudnetR GET POST
/new/lesson NewLessonR GET POST
/teacher/#Int ATeacherR GET
/student/#Int AStudentR GET
/lesson/#Int ALessonR GET
/lesson AllLessonR GET
/teacher AllTeacherR GET
/student AllStudentR GET
/show ShowR GET
|]
instance Yesod LessonChoosing

instance RenderMessage LessonChoosing FormMessage where
    renderMessage _ _ = defaultFormMessage


main = withSqliteConn ":memory:" $ runSqlConn action
  where
    action = do
        runMigration migrateAll
        newStudent (mkSId 1) "Mike"
        newStudent (mkSId 1) "Mike"
        newLesson (mkLId 1) "A" 1
        newLesson (mkLId 2) "A" 1
        ms <- choice (mkSId 1) (mkLId 1)
        liftIO $ print ms
        ms <- choice (mkSId 2) (mkLId 1)
        liftIO $ print ms
--      update (mkSId 3) [StudentName =. "Mi"]

newLesson lid name total = do
    insertKey lid $ Lesson name total 0

newTeacher tid name = do
    insertKey tid $ Teacher name

newStudent sid name = do
    insertKey sid $ Student name

getLesson lid = selectList [LessonId ==. lid] []

getTeacher tid = selectList [TeacherId ==. tid] []

getStudent sid = selectList [StudentId ==. sid] []

choice sid lid = do
    ml <- get lid
    case ml of
      Nothing -> return False
      Just les -> do
          if (lessonSelected les) >= (lessonTotalAvalible les)
              then return False
              else do
                  insert $ StudentLesson sid lid
                  update lid [LessonSelected =. ((lessonSelected les) + 1)]
                  (Just les)  <- get lid
                  if (lessonSelected les) > (lessonTotalAvalible les)
                      then rollback >> return False
                      else return True


mkLId :: GHC.Int.Int64 -> Key backend Lesson
mkLId key = Key $ PersistInt64 key

mkTId :: GHC.Int.Int64 -> Key backend Teacher
mkTId key = Key $ PersistInt64 key

mkSId :: GHC.Int.Int64 -> Key backend Student
mkSId key = Key $ PersistInt64 key

getRootR :: Handler RepHtml
getRootR = do
    defaultLayout [hamlet|
<a href=@NewStudentR> Add student
<a href=@NewStudentR> Add teacher
<a href=@NewStudentR> Add lesson
<a href=@AllStudentR> show all student
<a href=@AllTeacherR> show all teacher
<a href=@AllLessonR> show all lesson
|]