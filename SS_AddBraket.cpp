#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int fi;
    int ni;
    int val;
};

vector<Node> nums;
vector<Node> nums_cp;
vector<char> ops;

int nums_start_idx = 0;

Node createNode(int fi, int ni, int val) {
    Node* n = new Node();
    n->fi = fi;
    n->ni = ni;
    n->val = val;
    return *n;
}

int calc(int idx) {
    int ret;
    int nextidx = nums_cp[idx].ni;

    if (nextidx < 0) return -1;

    switch (ops[idx])
    {
    case '+': ret = nums_cp[idx].val + nums_cp[nextidx].val; break;
    case '-': ret = nums_cp[idx].val - nums_cp[nextidx].val; break;
    case '*': ret = nums_cp[idx].val * nums_cp[nextidx].val; break;
    default: break;
    }
    nums_cp[nextidx].val = ret;
    nums_cp[nextidx].fi = nums_cp[idx].fi;
    nums_cp[nums_cp[idx].fi].ni = nextidx;

    if (nextidx < nums_cp.size() - 1) {
        if (idx == nums_start_idx) nums_start_idx = nextidx;
        return nextidx + 1;
    }
    else {
        if (idx == nums_start_idx) nums_start_idx = nextidx;
        return -1;
    }
}

int getMax(int idx) {
    int ret = -1;
    for (int i = idx; i < nums_cp.size(); ++i) {
        int nextidx = calc(i);
        if (nextidx >= 0) int ret = getMax(nextidx);
        else {
            while (true) {
                nextidx = calc(nums_start_idx);
                if (nextidx < 0) return nums_cp[nums_cp.size()-1].val;
            }
        }
    }
    return ret;
}

int main() {
    int ninput, val;
    int nloop;
    char op;
    
    cin >> ninput;

    nloop = (ninput + 1) / 2;

    for (int i = 0; i < nloop; ++i) {
        cin >> val;
        int fi = i - 1;
        int ni = i + 1;
        if (i == 0) fi = -1;
        if (i == nloop - 1) ni = -1;
        nums.push_back(createNode(fi, ni, val));

        if (i < nloop - 1) {
            cin >> op;
            ops.push_back(op);
        }
    }

    printf("nums = [\n");
    for (int i = 0; i < nums.size(); ++i) {
        printf("(%d, %d, %d),\n", nums[i].fi, nums[i].ni, nums[i].val);
    }
    printf("]\n");
    printf("ops = [ ");
    for (int i = 0; i < ops.size(); ++i) {
        printf("%c ", ops[i]);
    }
    printf("]\n");

    int max_ret = 0;
    int ret = 0;
    if (nums.size() > 0) {
        for (int i = 0; i < nums.size() - 1; ++i) {
            nums_cp.clear();
            nums_cp.assign(nums.begin(), nums.end());
            int nextidx = calc(i);
            if (nextidx < 0) ret = nums_cp[nums_cp.size()-1].val;
            else ret = getMax(nextidx);
            if (ret > max_ret) max_ret = ret;
        }
    }
    printf("result: %d\n", max_ret);

    return 0;
}