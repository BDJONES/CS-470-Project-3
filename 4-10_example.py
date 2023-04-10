# Brute Force Method
# - Take every subset of the array and sum it
# - Return True/False in the NP Complete case
# - Return subset that sums closest to target sum without going over in NP Hard case

def brute_force_nph(arr, min_sum=0):
    best_subset = []
    best_sum = np.inf
    for i in range(1, len(arr)):
        for subset in itertools.combinations(arr, i):
            subset_sum = sum(subset)
            if subset_sum == min_sum:
#                 print('Solution Found: ', subset)
                return subset, subset_sum
            elif best_sum < subset_sum < min_sum:
                best_subset = subset
                best_sum = subset_sum
    return best_subset, best_sum


# # Greedy Methods (Approximation)
# - Iterate through the array and add values that reduce the current error
# - Can be done with sorting in O(nlogn) time to give at most 50% error

def greedy_nph(arr, min_sum=0, presort=True):
    if presort:
        arr = np.sort(arr)[::-1] # sort in decreasing order
    subset = []
    curr_sum = np.inf
    for val in arr:
        if val < min_sum and (curr_sum == np.inf or val < min_sum - curr_sum):
            subset.append(val)
            curr_sum = sum(subset)
    return subset, curr_sum

def write_dat(target, sequence, problem='ssum', email='nwcallahan'):
    ext = 'dat'
    file_path = f'{problem}_{email}.{ext}'
    with open(file_path, 'w') as f:
        f.write(f'{target}\n')
        for item in sequence:
            f.write(f'{item} {item}\n')
    print(f'Saved file to "{file_path}"')
    return file_path

target = 100
# sequence = [60,59,58,57,56,55,54,53,52,51,50,49,48,47,46,45,44,43,42,41]
sequence = [52, 51, 50, 49]

brute_subset, brute_sum = brute_force_nph(sequence, min_sum=target)
greedy_subset, greedy_sum = greedy_nph(sequence, min_sum=target)

err = lambda t, s : f'{((t - s) / t)*100}%' 

print('Brute Force Subset:', brute_subset)
print('Brute Force Error:', err(target, brute_sum))

print('Heuristic Subset:', greedy_subset)
print('Heuristic Error:', err(target, greedy_sum))

_ = write_dat(target, sequence)