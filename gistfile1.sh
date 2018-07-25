git filter-branch --commit-filter '
if [ "$GIT_COMMITTER_NAME" = "mfuluat" ];
then
        GIT_COMMITTER_NAME="Yazilimperver";
        GIT_AUTHOR_NAME="Yazilimperver";
        GIT_COMMITTER_EMAIL="Yazilimperver@gmail.com";
        GIT_AUTHOR_EMAIL="Yazilimperver@gmail.com";
        git commit-tree "$@";
else
        git commit-tree "$@";
fi' HEAD