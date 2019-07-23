call conda activate archery
call cd C:\Users\jsjtx\Desktop\1
call python example/main.py --dataset mpii -a hg --stacks 2 --blocks 1 --checkpoint checkpoint/mpii/new --resume checkpoint/mpii/hg_s2_b1/model_best.pth.tar -e
call cd C:\Users\jsjtx\Desktop\1\checkpoint\mpii\new
call python 4.py