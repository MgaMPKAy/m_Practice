module Handler.Blog
    ( getBlogR
    , postBlogR
    , getArticleR
    )
where

import Import

entryForm :: Form Article
entryForm = renderDivs $ Article
    <$> areq textField "Title" Nothing
    <*> areq nicHtmlField "Content" Nothing

getBlogR :: Handler RepHtml
getBlogR = do
    articles <- runDB $ selectList [][Desc ArticleTitle]
    ((_, articleWidget), enctype) <- generateFormPost entryForm
    defaultLayout $ do
        $(widgetFile "articles")

getArticleR :: ArticleId -> Handler RepHtml
getArticleR articleId = do
    article <- runDB $ get404 articleId
    defaultLayout $ do
        setTitle $ toHtml $ articleTitle article
        $(widgetFile "article")

postBlogR :: Handler RepHtml
postBlogR = do
    ((res, articleWidget), enctype) <- runFormPost entryForm
    case res of
      FormSuccess article -> do
          articleId <- runDB $ insert article
          setMessage $ toHtml $ (articleTitle article) <> " created"
          redirect $ ArticleR articleId
      _ -> defaultLayout $ do
          setTitle "Please correct your entry form"
          $(widgetFile "articleAddError")
