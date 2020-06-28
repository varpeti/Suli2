
/*/// Agent
var agentN = function()
{
    //*/// Heap (minified) //TODO faster node Heap
    var Heap=function(sort){this._array=[];this._sort=sort;Object.defineProperty(this,'length',{enumerable:true,get:function(){return this._array.length}});if(typeof this._sort!=='function'){this._sort=function(a,b){return a-b}}};Heap.prototype.push=function(node){node=node||{};this._array.push(node);this._bubble()};Heap.prototype.pop=function(){if(this.isEmpty()){return null}var top=this.peek();var last=this._array.pop();if(this.length>0){this._array[0]=last;this._sink()}return top};Heap.prototype.peek=function(){return this._array[0]};Heap.prototype.isEmpty=function(){return this.length===0};Heap.prototype._compare=function(i,j){return this._sort(this._array[i],this._array[j])>0};Heap.prototype._bubble=function(){var i=this.length-1;var j=this._parent(i);while(j!==null&&this._compare(i,j)){this._swap(i,j);i=j;j=this._parent(i)}};Heap.prototype._sink=function(){var i=0;var lc=this._left(i);var rc=this._right(i);var next;while(lc!==null){next=lc;if(rc!==null&&this._compare(rc,lc)){next=rc}if(this._compare(next,i)){this._swap(i,next);i=next;lc=this._left(i);rc=this._right(i)}else{return}}};Heap.prototype.print=function(){var s='';var nodes=1;var values=0;for(var i=0;i<this.length;i+=1){s+=' '+this._array[i].toString();values+=1;if(values===nodes){nodes=nodes<<1;values=0;s+='\n'}}console.log('\n'+s+'\n')};Heap.prototype._parent=function(i){var pi=(i-1)/2>>0;return pi>=0?pi:null};Heap.prototype._left=function(i){var li=i*2+1;return li<this.length?li:null};Heap.prototype._right=function(i){var ri=i*2+2;return ri<this.length?ri:null};Heap.prototype._swap=function(i,j){var a=this._array;var v=a[i];a[i]=a[j];a[j]=v};if(typeof module!=='undefined'){module.exports=Heap}
    
    //*/// Start
    var map;
    var path = [];
    var THE_HUGE_NUMBER = 99999;
    function start(c,mySelf,parent=null)
    {   
        initDraw();
        map = c; //TODO

        var startNode = new Node({x:mySelf.pos.x,y:mySelf.pos.y},0,THE_HUGE_NUMBER,false);
        if (!parent) 
            startNode.parent = startNode;
        else
            startNode.parent = parent;
        
        path = astar(startNode,getNeighbours);
        drawPath(path);
        console.log(path);
    }

    //*/// Callculate new center from old pos and cur pos
    function caclNewCenter(curPos,oldPos) // self.pos, self.oldpos
    {
        return {x: curPos.x+(curPos.x-oldPos.x), y: curPos.y+(curPos.y-oldPos.y)};
    }

    //*/// Wrapper around different line validators
    function isValidLine(p1,p2,c)
    {
        if (lc.validLine) return lc.validLine(p1,p2);
        else if (lc.validVisibleLine) return lc.validVisibleLine(c,p1,p2);
        else throw "Line validation function not found!";
    }

    //*/// Wraper around playerAt
    function isAnotherPlayeAt(p1,selfIndex)
    {
        var id = lc.playerAt(p1);
        return (id!=-1 && id!=selfIndex);
    }

    //*/// get next goal
    var trueGoal;
    function getNextGoal(pos)
    {
        if (trueGoal) return trueGoal;

        //find goal //TODO if there is no goal, the farrest road from the walls that right next to an unkown part of the map

        var goals = {x:0,y:0};
        var c     = 0;
        for (var x = 0; x < map.length; x++) 
        {
            for (var y = 0; y < map[x].length; y++) 
            {
                if (map[x][y]==100)
                {   
                    goals = {x:x+goals.x,y:y+goals.y};
                    c++;
                }
            }   
        }
        trueGoal = {x:goals.x/c,y:goals.y/c};
        drawCross({x1:trueGoal.x,y1:trueGoal.y,color:"#ff0000"});
        console.log(trueGoal);
        return trueGoal;
    }
    
    //*/// A*

    //*/// Heuristic
    function heuristic(pos)
    {
        goal = getNextGoal(pos);
        var l = (Math.abs(goal.x-pos.x)+Math.abs(goal.y-pos.y));
        return (Math.sqrt(8*l+1)-1)/2; // l=(x*(x+1))/2
    }

    //*/// Node
    var Node = function(pos,g,h,isGoal,step)
    {
        this.id = "x:"+pos.x+"y:"+pos.y;    //name      [string]  - unique, to increase the speed of the visited list(hash)   - astar          
        this.g = g;                         //cost      [number]  - overall cost to step into this node                       - getNeighbours
        this.goal = isGoal;                 //is a goal [boolean] - in case of multiple goals, it's easier to flag the nodes  - astar
        this.f = g + h;                     //the A* cost                                                                     - astar
        this.parent=undefined;              //parrent is storted to find the reverse path, and to calculate new center        - astar+getNeighbours
        this.pos = pos;                     //stored to calculate new center                                                  - getNeighbours
        this.step = step                    //stored to make the step                                                         - movefunction

        this.update = function(a)
        {
            this.g = a.g;
            this.f = a.f;
            this.parent= a.parent;
            this.step = a.step;
        }
    }

    //*/// getNeighbours
    function getNeighbours(cur,isAstar=true)
    {
        var newCenter; 
        newCenter = caclNewCenter(cur.pos,cur.parent.pos); //Parent allways exists

        var ret = [];

        for (var x = -1; x <= 1; x++)
            for (var y = -1; y <= 1; y++)
            {
                var pos  = {x:x+newCenter.x,y:y+newCenter.y};
                var cost = 1;
                if (!isValidLine(cur.pos,pos)) continue;
                if (!isAstar) 
                {
                    ret.push({pos:pos,step:{x:x,y:y}});
                    continue;
                }
                var node = new Node(
                    pos,                        // pos + id
                    cur.g+cost,                 // overall cost = cost to reach the parent (cur.g) + the road from parent to child (cost)
                    heuristic(pos),             // heuristic
                    (map[pos.x][pos.y]==100),   // is a goal?
                    {x:x,y:y}                   // step {-1,0,1}
                );
                ret.push(node);
            }
        return ret;
    }

    //*/// Astar
    var astar = function(start,getNeighbours)
    {
        var q = new Heap(function(a,b){return b.f-a.f;}); // Queue heap
        
        q.push(start);
    
        while (q.length>0)
        {   
            var cur = q.pop();

        
            //drawCross({x1:cur.pos.x,y1:cur.pos.y,color:"#ff00ff"});
            //if (cur.parent) drawLine({x1:cur.pos.x,y1:cur.pos.y,x2:cur.parent.pos.x,y2:cur.parent.pos.y,color:"#ff00ff"});
            //debugger;

            //console.log("---");
            //console.log(JSON.stringify(cur.id));
            //console.log(JSON.stringify(q));
    
            if (cur.goal) //If goal found, mine up the reverse path
            {
                var ret = [];
                while(cur.f!=THE_HUGE_NUMBER) 
                {
                    ret.push({pos:cur.pos,step:cur.step});
                    cur = cur.parent;
                }
                return ret.reverse();
            }
    
            var nextNodes = getNeighbours(cur);
    
            //console.log("+")
            if (nextNodes) for (var i = 0; i < nextNodes.length; i++) 
            {
                if (nextNodes[i].id == cur.id) continue; // Don't want to stay

                nextNodes[i].parent=cur;
                //console.log(JSON.stringify(nextNodes[i]));
                
                
                // This H4cK check if we have the node in the q
                // Id only contains the node coordinate, 
                // Technically this is not an astar anymore, it use less time and less memory but preforms worse.
                var inq = q._array.find(function(a){return a.id==nextNodes[i].id;});
                if (!inq) //new
                {
                    q.push(nextNodes[i]);
                }
                else //in the q
                {
                    inq.update(nextNodes[i]); //Update
                    q._bubble(); //Rebalance
                }

                //Draw
                //drawCross({x1:nextNodes[i].pos.x,y1:nextNodes[i].pos.y,color:"#00ffff"});
                //drawLine({x1:cur.pos.x,y1:cur.pos.y,x2:nextNodes[i].pos.x,y2:nextNodes[i].pos.y,color:"#00ffff"});
            }

            //console.log("---");
        }
        //debugger;
        return []; //No path found
    }

    //*/// Init
    this.init = function(c,playerData,selfIndex)
    {
        var mySelf = playerData[selfIndex];
        //setTimeout(function(){start(c,mySelf);},1); //Async!
        start(c,mySelf);
    }

    //*/// Panic
    function panic(c,playerData,selfIndex)  
    {   
        var mySelf = playerData[selfIndex];
        mySelf.parent = {pos:mySelf.oldpos};
        var nbs = getNeighbours(mySelf,false);
        var nextPos  = {x:mySelf.pos.x,y:mySelf.pos.y};
        var nextStep = {x:0,y:0};
        //debugger;
        for (var i = 0; i < nbs.length; i++) 
        {
            if (!isAnotherPlayeAt(nbs[i].pos)) {nextPos = nbs[i].pos; nextStep = nbs[i].step; break;}
        }
        setTimeout(function(){start(c,{pos:nextPos},mySelf);},1); //Async!
        return nextStep;
    }

    //*/// Move
    this.movefunction = function(c,playerData,selfIndex)
    {
        if (path.length>0)
        {
            var mySelf = playerData[selfIndex];
            var nextStep = {x:path[0].step.x,y:path[0].step.y};
            var nextPos  = {x:path[0].pos.x, y:path[0].pos.y };
            //setTimeout(function(){start(c,{pos:nextPos},mySelf);},1); //Async!
            path.shift();
            if (lc.playerAt(nextPos)!=-1) return panic(c,playerData,selfIndex);
            return nextStep;
        }
        return panic(c,playerData,selfIndex);
    }

    //*/// Draw - try{}catch(e){} everything!

    var au = 20;
    var initDraw = function()
    {
        try
        {
            au = d3.select("#track")[0][0].children[0].width.baseVal.value;
        }
        catch (e)
        {
        }
    }

    var dpath = [];
    var drawPath = function(path)
    {
        try 
        {
            //remove old path
            for (var i = 0; i < dpath.length; i++) 
            {
                dpath[i].remove();
            }
    
    
                var l = {x1:0,y1:0,x2:0,y2:0,color:"#1122ff"};
                for (var i = 1; i < path.length; i++) 
                {
                    l.x1 = path[i-1].pos.x;
                    l.y1 = path[i-1].pos.y;
                    l.x2 = path[i].pos.x;
                    l.y2 = path[i].pos.y;
                    dpath.push(drawCross(l));
                    dpath.push(drawLine(l));
            }
        }
        catch (e)
        {
        }
    }

    var drawLine=function(l)
    {
        try
        {
            var pline = d3.select("#playerlines")
                .append("line")
                .attr("x1", l.y1*au)
                .attr("y1", l.x1*au)
                .attr("x2", l.y2*au)
                .attr("y2", l.x2*au)
                .style("fill", 'transparent')
                .style("stroke", l.color)
                .style("stroke-width", '3')
            return pline;
        }
        catch (e)
        {
        }
        
    }

    var drawCross=function(l)
    {
        try
        {
            var pcross = d3.select("#playercrosses")
                    .append("g");
            pcross.append("line")
                    .attr("x1", l.y1*au-au/4)
                    .attr("y1", l.x1*au-au/4)
                    .attr("x2", l.y1*au+au/4)
                    .attr("y2", l.x1*au+au/4)
                    .style("fill", 'transparent')
                    .style("stroke", l.color)
                    .style("stroke-width", '2');
            pcross.append("line")
                    .attr("x1", l.y1*au+au/4)
                    .attr("y1", l.x1*au-au/4)
                    .attr("x2", l.y1*au-au/4)
                    .attr("y2", l.x1*au+au/4)
                    .style("fill", 'transparent')
                    .style("stroke", l.color)
                    .style("stroke-width", '2');
            return pcross;
        }
        catch (e)
        {
        }
    }

    /*///
};

//* /// Injection
(function inject()
{
    for (var i = 0; i < 1; i++)
    {
        var a = new agentN;
        lc.addPlayer("agent"+i,a);
    }

    //var b = new agentB;
    //lc.addPlayer("agentB",b);

    document.getElementById("start-codeplay").click(); //start
})();

//*/// Must contain a new line after a comment!
