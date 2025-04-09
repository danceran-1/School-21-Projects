
from analytics import Research
import config


def main():
    
   
    try:
        has_header = True
        out = Research(config.file_path,has_header)
        data = out.file_reader()
        analytics = Research.Analytics(data)
        telegram = out.generate_report(data)
        
        result = [list(map(int, line.split(','))) for line in data]
        a = Research.Calculations(data)
        counts = a.counts()
        fractions = Research.Calculations.fractions(counts)
        predict = analytics.predict_random(config.num_of_steps)
        last = analytics.predict_last()

        predicted_heads = sum(pred[0] for pred in predict)
        predicted_tails = sum(pred[1] for pred in predict)

        report = config.report_template.format(
            observations=len(data),
            tails=counts[1],
            heads=counts[0],
            tail_percent=fractions[1],
            head_percent=fractions[0],
            steps=config.num_of_steps,
            predicted_heads=predicted_heads,
            predicted_tails=predicted_tails,
            )
        analytics.save_file(report, "report", "txt")

        print(result)
        print(*counts)
        print(*fractions)
        print(predict)
        print([last])
    except FileNotFoundError as e:
        print(f"Error: {e}")
    except ValueError as e:
        print(f"Error: {e}")
    except Exception as e:
        print(f"Unexpected error: {e}")

if __name__ == '__main__':
    main()

