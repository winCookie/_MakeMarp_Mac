---
marp: true
paginate: true
math: katex
style: |
    section {
        display: flex;
        justify-content: space-between;
    }
    .column {
        flex: 1;
        padding: 10px;
    }
---

## 双指针基本类型
# 分栏示例

<div class="column">
- 第一列内容
- 第一列内容
</div>

<div class="column">
- 第二列内容
- 第二列内容
</div>

---

### 1. 同向双指针

两个指针从同一侧开始，都向同一方向移动

**特点**：
- 指针移动方向相同
- 通常用于滑动窗口问题
- 时间复杂度 $O(n)$

---

## 代码实现

```cpp
// 同向双指针通用模板
void sameDirectionTwoPointers(int arr[], int n) {
    int left = 0;
    
    for (int right = 0; right < n; right++) {
        while (left <= right && condition) {
            left++;
        }
        // 更新答案
    }
}