class state:
    def __init__(self,ship,missionaries,savages):
        self.ship=ship
        self.missionaries=missionaries
        self.savages=savages
    def __eq__(self,other):
        if isinstance(other, state):
            return self.ship == other.ship and self.missionaries == other.missionaries and self.savages==other.savages
        return False
    def __hash__(self):
        return hash((self.ship,self.missionaries,self.savages))
    def trans(self,missionaries,savages):
        if self.ship==0:
            if missionaries>self.missionaries:
                return 0
            if savages>self.savages:
                return 0
            if (self.missionaries-missionaries)<(self.savages-savages) and (self.missionaries-missionaries)!=0:
                return 0
            if (3-self.missionaries+missionaries)<(3-self.savages+savages) and self.missionaries-missionaries!=3:
                return 0
            self.missionaries=self.missionaries - missionaries
            self.savages=self.savages - savages
            self.ship=1
            return 1
        elif self.ship==1:
            if missionaries>3-self.missionaries:
                return 0
            if savages>3-self.savages:
                return 0
            if (3-self.missionaries-missionaries)<(3-self.savages-savages) and (3-self.missionaries-missionaries)!=0:
                return 0
            if (self.missionaries+missionaries)<(self.savages+savages) and 3-self.missionaries-missionaries!=3:
                return 0
            self.missionaries=self.missionaries + missionaries
            self.savages=self.savages + savages
            self.ship=0
            return 1


def BFS(primary):
    thislist=[primary]#BFS队列
    thisdict={primary:[(primary.ship,primary.missionaries,primary.savages)]}#路径
    thisset={primary}#是否访问过
    method=[(1,0),(0,1),(2,0),(0,2),(1,1)]
    while 1:
        if len(thislist)==0:
            break
        now=thislist.pop(0)
        list=thisdict[now].copy()
        flag=0
        for x in method:
            temp=state(now.ship,now.missionaries,now.savages)
            f=temp.trans(x[0],x[1])
            g=temp in thisset
            if f and g==False:
                thislist.append(temp)#该状态入队
                thisset.add(temp)#标记为已访问
                thisdict[temp]=list.copy()
                thisdict[temp].append((temp.ship,temp.missionaries,temp.savages))#记录路径
                if temp.savages==0 and temp.missionaries==0:
                    flag=1
                    break
        if flag==1:
            break

    n=len(thislist)
    if n==0:
        print("no way")
    else:
        temp=thislist.pop()
        for i in thisdict[temp]:
            print(i)


primary=state(0,3,3)
BFS(primary)
