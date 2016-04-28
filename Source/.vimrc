set nocompatible

set enc=utf-8
set fenc=utf-8

set tabstop=4
set softtabstop=4
set shiftwidth=4
set backspace=2
set autoindent
set cindent

syntax on
set t_Co=256
set number
set showmatch
set hls

autocmd FileType cpp nnoremap <F9> :w <bar> :! g++ % -std=c++11 -O2 -Wall && ./a.out<CR>
