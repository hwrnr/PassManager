
#PassManager
_passfold(){
    local cmd="${1##*/}"
    local word=${COMP_WORDS[COMP_CWORD]}
    local line=${COMP_LINE}

    COMPREPLY=($(compgen -W  "$(ls ${HOME}/PassFold/)" -- "${word}"))
}
complete -F _passfold passread

