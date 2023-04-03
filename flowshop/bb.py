import sys

# Calculate partial makespan given the current sequence
def calculate_partial_makespan(sequence, processing_times):
    num_jobs = len(sequence)
    num_machines = len(processing_times[0])
    completion_times = [[0] * num_machines for _ in range(num_jobs)]

    for job in range(num_jobs):
        for machine in range(num_machines):
            if machine == 0 and job == 0:
                completion_times[job][machine] = processing_times[sequence[job]][machine]
            elif machine == 0:
                completion_times[job][machine] = completion_times[job - 1][machine] + processing_times[sequence[job]][machine]
            elif job == 0:
                completion_times[job][machine] = completion_times[job][machine - 1] + processing_times[sequence[job]][machine]
            else:
                completion_times[job][machine] = max(completion_times[job - 1][machine], completion_times[job][machine - 1]) + processing_times[sequence[job]][machine]

    return completion_times[-1][-1]

# Recursive branch and bound search function
def search(sequence, remaining_jobs, processing_times, min_makespan):
    if not remaining_jobs:
        current_makespan = calculate_partial_makespan(sequence, processing_times)
        if current_makespan < min_makespan[0]:
            min_makespan[0] = current_makespan
            return

    for job in remaining_jobs:
        # Add job to the sequence
        sequence.append(job)

        # Bounding condition: Check if the current partial makespan is already larger than the current minimum
        current_partial_makespan = calculate_partial_makespan(sequence, processing_times)
        if current_partial_makespan < min_makespan[0]:
            remaining_jobs.remove(job)
            search(sequence, remaining_jobs, processing_times, min_makespan)
            remaining_jobs.add(job)

        # Remove job from the sequence
        sequence.pop()

# Branch and bound algorithm for finding the minimum makespan
def branch_and_bound(processing_times):
    num_jobs = len(processing_times)
    min_makespan = [sys.maxsize]
    search([], set(range(num_jobs)), processing_times, min_makespan)
    return min_makespan[0]

# Example usage
processing_times = [
    [0 ,12, 24],
    [24, 12, 24],
    [24, 12, 24],
    [24, 12, 0],
    [0, 4, 0],
    [0, 4, 0],
    [0, 4, 0],
    [0, 4, 0],
    [0, 4, 0],
    [0, 4, 0],
    [0, 4, 0],
    [0, 4, 0],
    [0, 4, 0],
]

min_makespan = branch_and_bound(processing_times)
print(f'Minimum makespan: {min_makespan}')
