(custom-set-variables
  ;; custom-set-variables was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(c-default-style (quote ((c-mode . "linux") (java-mode . "java") (awk-mode . "awk") (other . "gnu"))))
 '(debug-on-error nil)
 '(haskell-indent-after-keywords (quote (("where" 2 0) ("of" 2) ("do" 4) ("in" 2 0) ("{" 2) "if" "then" "else" "let")))
 '(haskell-indent-dont-hang (quote ("(")))
 '(haskell-indent-offset 4)
 '(haskell-indent-thenelse 4)
 '(inhibit-startup-screen t)
 '(make-backup-files nil)
 '(yas/prompt-functions (quote (yas/dropdown-prompt yas/x-prompt yas/completing-prompt yas/ido-prompt yas/no-prompt))))
(custom-set-faces
  ;; custom-set-faces was added by Custom.
  ;; If you edit it by hand, you could mess it up, so be careful.
  ;; Your init file should contain only one such instance.
  ;; If there is more than one, they won't work right.
 '(show-paren-match ((((class color) (background dark)) (:foreground "green1")))))

;; ================================ Basic UI  =================================
(menu-bar-mode nil)
(tool-bar-mode nil)
(show-paren-mode t)
(scroll-bar-mode nil)
(fset 'yes-or-no-p 'y-or-n-p)

(put 'set-goal-column 'disabled nil)
;;(sml-modeline-mode t)

;; Rainbow-delimiters
(add-to-list 'load-path "~/.emacs.d/extensions")
;(require 'rainbow-delimiters)

;; Frame-title
(setq frame-title-format
      '(:eval
	(if buffer-file-name
	    (replace-regexp-in-string
	     (getenv "HOME") "~"
	     (concat (file-name-directory buffer-file-name) "%b"))
	  (buffer-name))))

;; ============================= C Mode ===============================
(setq c-set-style "K&R")
(setq tab-width 8)
(setq c-basic-offset 8)
(setq indent-tabs-mode t)

;; ============================= Other Laguage ==============================
;; Go mode
;;(require 'go-mode-load)

;; Haskell mode
(load "~/.emacs.d/extensions/haskell-mode-2.8.0/haskell-site-file.el")
(add-hook 'haskell-mode-hook 'turn-on-haskell-doc-mode)
;;(add-hook 'haskell-mode-hook 'turn-on-haskell-simple-indent)
;;(add-hook 'haskell-mode-hook 'turn-on-haskell-indentation)
(add-hook 'haskell-mode-hook 'turn-on-haskell-indent)
;;(setq haskell-font-lock-symbols t)
(add-to-list 'exec-path "~/.cabal/bin/")
(add-to-list 'load-path "~/.emacs.d/extensions/ghc-mod/")
(autoload 'ghc-init "ghc" nil t)
(add-hook 'haskell-mode-hook (lambda () (ghc-init)(flymake-mode)))

;;nxhtml
(load "~/.emacs.d/extensions/nxhtml/autostart.elc")

;; Lua
;;(require 'lua-mode)
;;(setq auto-mode-alist (cons '("\\.lua$" . lua-mode) auto-mode-alist))
;;(autoload 'lua-mode "lua-mode" "Lua editing mode." t)
;;(add-hook 'lua-mode-hook 'turn-on-font-lock)
;;(add-hook 'lua-mode-hook 'hs-minor-mode t)

;; ============================= Org Mode ===============================
(add-to-list 'load-path "~/.emacs.d/extensions/org-7.5/lisp")
(add-to-list 'load-path "~/.emacs.d/extensions/org-7.5/contrib/lisp")
(require 'org-install)

;; ===========================Editing Helpers =================================

;; YASnippet
(add-to-list 'load-path "~/.emacs.d/extensions/yasnippet-0.6.1c/")
(require 'yasnippet)
(yas/initialize)
(yas/load-directory "~/.emacs.d/extensions/yasnippet-0.6.1c/snippets")

;; Hippie-expand
(global-set-key [(meta ?/)] 'hippie-expand)
(setq hippie-expand-try-functions-list
      '(try-expand-dabbrev
	try-expand-dabbrev-visible
	try-expand-dabbrev-all-buffers
	try-expand-dabbrev-from-kill
	try-complete-file-name-partially
	try-complete-file-name
	try-expand-all-abbrevs
	try-expand-list
	try-expand-line
	try-complete-lisp-symbol-partially
	try-complete-lisp-symbol))

;; Auto-complete (Evil)
(add-to-list 'load-path "~/.emacs.d/extensions/auto-complete")
(setq ac-dict-dictionary "~/.emacs.d/extensions/auto-complete/ac-dict")
(require 'go-autocomplete)
(require 'auto-complete-config)
(add-to-list 'ac-dictionary-directories ac-dict-dictionary)
(ac-config-default)
(setq ac-auto-start 2)
(setq ac-auto-show-menu nil)
(setq ac-ignore-case nil)
(define-key ac-completing-map "\t" 'ac-complete)
;(define-key ac-completing-map "\n" 'ac-complete)

(define-globalized-minor-mode real-global-auto-complete-mode
  auto-complete-mode (lambda ()
                       (if (not (minibufferp (current-buffer)))
			   (auto-complete-mode 1))
                       ))
(real-global-auto-complete-mode t)

;; C-context-line-break
(defun my-c-do-indent ()
  "For c-mode context line break"
  (define-key c-mode-base-map "\C-m" 'c-context-line-break))
(add-hook 'c-initialization-hook 'my-c-do-indent)

;; Ruby-context-line-break
;; (defun my-ruby-context-line-break ()
;;   "Simple ruby context line break workround"
;;   (ruby-indent-line))
;; (defun my-ruby-do-indent ()
;;   "For c-mode context line break"
;;   (define-key ruby-mode-map "\C-m" 'c-context-line-break))
;;(Add-hook 'ruby-mode-hook 'my-ruby-do-indent)

(defface ac-yasnippet-candidate-face
  '((t (:background "sandybrown" :foreground "black")))
  "Face for yasnippet candidate.")
(defface ac-yasnippet-selection-face
  '((t (:background "coral3" :foreground "white")))
  "Face for the yasnippet selected candidate.")
(defvar ac-source-yasnippet
  '((candidates . ac-yasnippet-candidate)
    (action . yas/expand)
    (candidate-face . ac-yasnippet-candidate-face)
    (selection-face . ac-yasnippet-selection-face))
  "Source for Yasnippet.")

;; ================================ MISC =====================================

;; Move forward to Nth occurence of CHAR.
(defun wy-go-to-char (n char)
  "Move forward to Nth occurence of CHAR.
   Typing `wy-go-to-char-key' again will move forwad to the next Nth
   occurence of CHAR."
  (interactive "p\ncGo to char: ")
  (search-forward (string char) nil nil n)
  (while (char-equal (read-char)
		     char)
    (search-forward (string char) nil nil n))
  (setq unread-command-events (list last-input-event)))
(define-key global-map (kbd "C-c a") 'wy-go-to-char)

;; Remove trailing whilespace when save file
;; (add-hook 'before-save-hook (lambda () (delete-trailing-whitespace)))

;; Kill buffer
(global-set-key (kbd "M-C-k") 'kill-this-buffer)

;;(add-to-list 'load-path "~/.emacs.d/extensions/magit-1.0.0/")
;;(require 'magit)

(defun auto-recompile-emacs-file ()
  (interactive)
  (when (and buffer-file-name (string-match "\\.emacs" buffer-file-name))
    (let ((byte-file (concat buffer-file-name "\\.elc")))
      (if (or (not (file-exists-p byte-file))
	      (file-newer-than-file-p buffer-file-name byte-file))
	  (byte-compile-file buffer-file-name)))))
;;(add-hook 'after-save-hook 'auto-recompile-emacs-file)

;; occur in multi-buffer
(eval-when-compile
  (require 'cl))

(defun get-buffers-matching-mode (mode)
  "Returns a list of buffers where their major-mode is equal to MODE"
  (let ((buffer-mode-matches '()))
   (dolist (buf (buffer-list))
     (with-current-buffer buf
       (if (eq mode major-mode)
           (add-to-list 'buffer-mode-matches buf))))
   buffer-mode-matches))

(defun multi-occur-in-this-mode ()
  "Show all lines matching REGEXP in buffers with this major mode."
  (interactive)
  (multi-occur
   (get-buffers-matching-mode major-mode)
   (car (occur-read-primary-args))))

;; global key for `multi-occur-in-this-mode' - you should change this.
(global-set-key (kbd "C-<f2>") 'multi-occur-in-this-mode)

(global-unset-key [(control z)])
(global-unset-key [(control x)(control z)])
(global-set-key (kbd "C-x a r") 'align-regexp)
(global-set-key (kbd "<f5>") 'compile)

(put 'upcase-region 'disabled nil)
(put 'downcase-region 'disabled nil)
;; (global-set-key [(control z)] 'undo)

;; ============== Color Theme =============================
;;(add-to-list 'load-path "~/.emacs.d/extensions/color-theme-6.6.0/")
;;(add-to-list 'load-path "~/.emacs.d/extensions/color-theme-6.6.0/themes")
;;(require 'color-theme)
;;(eval-after-load "color-theme"
;;  '(progn
;;     (color-theme-initialize)
;;     (color-theme-hober)))
;;(color-theme-initialize)
;;(require 'color-theme-solarized)
;;(color-theme-solarized)

;; ============================ Verilog mode ========================
(require 'verilog-mode)
(setq verilog-compiler "iverilog")
(setq verilog-coverage "covered")
(setq verilog-simulator "vvp")
(setq verilog-linter "")

;; ============================ IDO ==================================
(require 'ido)
(ido-mode)
(setq ido-enable-flex-matching t)
(require 'smex)

;; ========================== Repeat insert ============================
(require 'repeat-insert)

;; =========================== Speedbar ===============================
(require 'speedbar)
(speedbar-add-supported-extension ".hs")

;; (add-to-list 'which-func-modes 'haskell-mode)
;; (which-func-mode 1)

;; =========================== Markdown ===============================
(autoload 'markdown-mode "markdown-mode.el"
   "Major mode for editing Markdown files" t)
(setq auto-mode-alist
   (cons '("\\.md" . markdown-mode) auto-mode-alist))

;; =========================== Scala =================================
(add-to-list 'load-path "~/.emacs.d/extensions/scala-mode/")
(require 'scala-mode-auto)

;; =========================== Flymake ==============================
;; Nothing now