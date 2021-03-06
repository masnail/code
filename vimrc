syntax on
set nu
"colorscheme darkblue
set noswapfile
set nobackup
set mouse=a

filetype on

"set cursorline
"set cursorcolumn

set autoindent
set cindent
set smartindent

"set expandtab " space grid replace tab
set backspace=2
set tabstop=4
set shiftwidth=4
set softtabstop=4

set linebreak
set showmatch

"设置打开文件时的编码
set fileencodings=utf-8,gb2312,gbk,gb18030
set termencoding=utf-8
"set fileformats=unix
"set encoding=prc
set encoding=utf-8

set hlsearch
set incsearch

set laststatus=2
set ruler

"no \n
set nowrap

"显示行号 
set nu
"set cursorline

set dictionary +=/usr/include

"设置tab???
set ts=4

"搜索的内容高???
set hlsearch


"打开语法高亮 
syntax enable
syntax on 

"set cursorcolumn

set autoindent
set cindent
set smartindent
set softtabstop=4 
set shiftwidth=4 


"自动缩进设置 
set cindent 
set smartindent 
set incsearch 
set autoindent 


"Show matching bracets 
set showmatch 


"Get out of VI's compatible mode 
set nocompatible 


"Have the mouse enabled all the time 
set mouse=a


"Set to auto read when a file is changed from the outside 
set autoread 


"Enable filetype plugin 
filetype plugin on 
filetype indent on 


"设置配色方案为torte 
colo torte 


"设置编辑的文件保存时的编码方???
set fileencoding=utf-8



"显示括号匹配情况
set magic


"右下角显示光标状态行
set ruler


"设置Ctrl+c复制
vmap <C-c> "+y


"设置退格键和delete键删???
set backspace=indent,eol,start


"set cscope
set cscopequickfix=s-,c-,d-,i-,t-,e-


"设置记录的历史操作列???
set history=100 


"设置折叠 
set foldcolumn=2 
set foldmethod=indent 
set foldlevel=3

"新建文件后，自动定位到文件末???
autocmd BufNewFile * normal G 



"绑定自动补全的快捷键<C-X><C-O>???leader>; 
imap <leader>; <C-X><C-O> 


"设定开关Taglist插件的快捷键为F4，可以在VIM的左侧栏列出函数列表???
map <F4> :Tlist<CR> 


"设置程序的运行和调试的快捷键F5和Ctrl-F5 
map <F5> :call CompileRun()<CR> 
map <C-F5> :call Debug()<CR> 


"设置tab操作的快捷键，绑???tabnew???leader>t，绑???tabn, :tabp???leader>n, 
"<leader>p 
map <leader>t :tabnew<CR> 
map <leader>n :tabn<CR> 
map <leader>p set tags=tags; :tabp<CR> 


"用cscope支持 
set csprg=/usr/bin/cscope 
let Tlist_Ctags_Cmd='/usr/bin/ctags' 
let Tlist_Show_One_File=1 
let Tlist_Exit_OnlyWindow=1 
let Tlist_Use_Left_Window=1 

set tags=tags; 
