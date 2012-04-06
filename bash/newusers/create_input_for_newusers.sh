LINE_TEMPLATE='$name:$passwd:$uid:$gid:$gecos:$dir:$shell'
PWLEN=12

function read_random_pw { 
    local len=$1
    local pw=$(dd if=/dev/urandom bs=1k count=1 2>/dev/null | base64 | head -c $len)
    echo $pw
}

while read username comment; do
    # "line" is "username comment"
    if [[ -z $username && -z $comment ]]; then 
        continue; 
    fi
    if [[ -z $comment ]]; then
        echo "Wrong input. Give a <username> <comment> per line."
        exit 1
    fi
    passwd=$(read_random_pw $PWLEN)
    printf "%s:%s:::%s:/home/%s:/bin/bash\n" "$username" "$passwd" "$comment" "$username"
done
