import sys


def call_add(clients, recipients):
    client_set = set(clients)
    recipient_set = set(recipients)
    return list(client_set - recipient_set)


def for_new_client(clients, participants):
    client_set = set(clients)
    par_set = set(participants)
    return list(par_set - client_set)


def for_new_par(clients, participants):
    client_set = set(clients)
    par_set = set(participants)
    return list(client_set - par_set)


def main():

    clients = ['andrew@gmail.com', 'jessica@gmail.com', 'ted@mosby.com',
               'john@snow.is', 'bill_gates@live.com', 'mark@facebook.com',
               'elon@paypal.com', 'jessica@gmail.com']
    participants = ['walter@heisenberg.com', 'vasily@mail.ru',
                    'pinkman@yo.org', 'jessica@gmail.com', 'elon@paypal.com',
                    'pinkman@yo.org', 'mr@robot.gov', 'eleven@yahoo.com']
    recipients = ['andrew@gmail.com', 'jessica@gmail.com', 'john@snow.is']

    if len(sys.argv) != 2:
        print("Example: python3 marketing.py <task_name>")
        print("Available tasks: call_center, potential_clients, loyalty_program")
        sys.exit(1)

    task = sys.argv[1]

    if task == "call_center":
        result = call_add(clients, recipients)
        print("Call center list:", result)
    elif task == "potential_clients":
        result = for_new_client(clients, participants)
        print("Potential clients list:", result)
    elif task == "loyalty_program":
        result = for_new_par(clients, participants)
        print("Loyalty program list:", result)
    else:
        raise ValueError(
            "Invalid task name. Choose from: call_center, potential_clients, loyalty_program.")


if __name__ == '__main__':
    main()
