import Network.CGI
import Text.Html

main :: IO ()
main = runCGI (handleErrors cgiMain)

cgiMain :: CGI CGIResult
cgiMain = output $ renderHtml $ do
   [header $ thetitle << "Test Cgi"
    , body <<
    [h1 << "Learn Cgi in Haskell"
     , paragraph <<
       [primHtml "Hello,World!"]]]
