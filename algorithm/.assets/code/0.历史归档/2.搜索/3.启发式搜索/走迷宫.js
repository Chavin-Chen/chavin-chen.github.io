class Coord {
    x = 0;
    y = 0;
    dis0 = 0; // 到起始点距离 G
    from = -1; // 上一个坐标，路径记录
    constructor(x, y, dis0 = 0, from = -1) {
        this.x = x;
        this.y = y;
        this.dis0 = dis0;
        this.from = from;
    }
    dist(c) { // 曼哈顿距离
        return Math.abs(this.x - c.x) + Math.abs(this.y - c.y)
    }
    toString() { // unique
        return `${this.x},${this.y}`
    }
}
/**
 * try add c to choice
 */
function add(G, visited, choice, c) {
    if (G[c.x]?.[c.y] !== 0) {
        return;
    }
    if (visited.has(c.toString())) {
        return;
    }
    choice.push(c);
}

/**
 * A-star for shortest path from start to ended
 */
function dfs(G, start, ended) {
    const nodes = []; // 记录所有访问过的坐标
    const choice = [start]; // 可达坐标
    const visited = new Set(choice); // 访问去重
    const path = []; // 最短路径
    let idx, it;
    while (choice.length > 0) {
        // 启发搜索
        idx = -1;
        choice.reduce((min, e, i) => {
            // F=min(G + H)
            if (e.dis0 + e.dist(ended) < min) {
                idx = i;
                return e.dis0 + e.dist(ended);
            }
            return min;
        }, Number.MAX_SAFE_INTEGER);
        if (idx < 0) {
            path.splice(0, path.length);
            break; // 无法到达
        }
        it = choice[idx];
        choice.splice(idx, 1);
        if (it.toString() === ended.toString()) {
            do {
                path.push(it);
                it = nodes[it.from];
            } while (it);
            break; // 到达终点
        }
        nodes.push(it);
        visited.add(it.toString());
        // 添加可达的路径
        add(G, visited, choice, new Coord(it.x - 1, it.y, it.dis0 + 1, nodes.length - 1));
        add(G, visited, choice, new Coord(it.x + 1, it.y, it.dis0 + 1, nodes.length - 1));
        add(G, visited, choice, new Coord(it.x, it.y - 1, it.dis0 + 1, nodes.length - 1));
        add(G, visited, choice, new Coord(it.x, it.y + 1, it.dis0 + 1, nodes.length - 1));
    }
    return path.reverse();
}

// main 
const path = dfs([
    [0, 0, 0, 0, 0],
    [0, 1, 1, 1, 0],
    [0, 0, 0, 1, 0],
    [0, 0, 0, 1, 0],
    [0, 0, 0, 1, 0], // [0, 0, 0, 0, 0]
], new Coord(2, 2), new Coord(0, 4));
if (!path.length) {
    console.log('unreachable');
} else {
    console.log('total:', path[path.length - 1].dis0);
    for (let c of path) {
        console.log(c);
    }
}