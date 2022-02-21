cat << EOF > .git/hooks/pre-commit
#!/bin/bash

echo "Pulling ..."
git pull
EOF

chmod +x .git/hooks/pre-commit

cat << EOF > .git/hooks/pre-push
#!/bin/bash

echo "Pulling ..."
git pull
EOF

chmod +x .git/hooks/pre-push